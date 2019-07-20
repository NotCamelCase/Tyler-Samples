#include <Tyler/RenderContext.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Display.h"

using namespace tyler;

// Vertex layout
struct Vertex
{
    glm::vec4   m_Pos;
};

// Optional args to be passed to app
struct Optional
{
    int32_t     m_SDLRendererIdx = 1;
    uint32_t    m_ScreenWidth = 1280;
    uint32_t    m_ScreenHeight = 768u;
    bool        m_DisplayFullscreen = false;
};

bool ParseCommandLine(int argc, char** ppArgv, RasterizerConfig* pConfig, Optional* pOptional);

glm::vec4 VS(VertexInput* pVertexInput, VertexAttributes* pVertexAtributes, ConstantBuffer* pConstantBuffer)
{
    Vertex& vertex = *reinterpret_cast<Vertex*>(pVertexInput);

    return vertex.m_Pos;
}

void FS(InterpolatedAttributes* pVertexAttributes, ConstantBuffer* pConstantBuffer, FragmentOutput* pFragmentOut)
{
    // Simple red triangle
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[0]), _mm_setr_ps(1.f, 0.f, 0.f, 1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[1]), _mm_setr_ps(1.f, 0.f, 0.f, 1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[2]), _mm_setr_ps(1.f, 0.f, 0.f, 1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[3]), _mm_setr_ps(1.f, 0.f, 0.f, 1.f));
}

int main(int argc, char** ppArgv)
{
    Optional opt = {};
    RasterizerConfig config = {};
    if (!ParseCommandLine(argc, ppArgv, &config, &opt)) return 0;

    RenderContext* pRenderContext = new RenderContext(config);
    if (!pRenderContext->Initialize())
    {
        assert(false && "RenderContext failed to initialize!");

        delete pRenderContext;
    }

    // Allocate color & depth buffers
    uint8_t* pColorBuffer = new uint8_t[opt.m_ScreenWidth * opt.m_ScreenHeight * 4]; // Color buffer format == R8G8B8A8_UNORM
    float* pDepthBuffer = new float[opt.m_ScreenWidth * opt.m_ScreenHeight]; // Depth buffer format == D32_FLOAT

    Display* pDisplay = new Display(pColorBuffer, opt.m_SDLRendererIdx, opt.m_ScreenWidth, opt.m_ScreenHeight, opt.m_DisplayFullscreen, "Hello, Triangle!");

    // Set up main FBO
    Framebuffer fbo = {};
    fbo.m_pColorBuffer = pColorBuffer;
    fbo.m_pDepthBuffer = pDepthBuffer;
    fbo.m_Width = opt.m_ScreenWidth;
    fbo.m_Height = opt.m_ScreenHeight;

    // No vertex attribute is used
    ShaderMetadata metadata = { 0, 0, 0 };

    //CCW
    glm::vec4 vertices[] =
    {
        { -0.5f, 0.5f, 1.f, 1.f },
        { 0.5f, 0.5f, 1.f, 1.f },
        { 0.f, -0.5f, 1.f, 1.f }
    };

    uint32_t indices[] = { 0, 1, 2 };

    // Bind FBO to be used in subsequent render pass once
    pRenderContext->BindFramebuffer(&fbo);

    // Bind VBO and set buffer stride
    pRenderContext->BindVertexBuffer(vertices, sizeof(Vertex));
    // Bind IBO
    pRenderContext->BindIndexBuffer(indices);

    // Bind shader, constant buffer, texture(s)
    pRenderContext->BindShaders(VS, FS, metadata);

    SDL_Event event;
    bool running = true;
    bool paused = false;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    paused = !paused;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    running = false;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
            }
        }

        if (!paused) // When unpaused, re-draw every frame
        {
            const auto drawBegin = std::chrono::high_resolution_clock::now();

            pDisplay->ClearRenderTarget();

            // Clear RT
            pRenderContext->BeginRenderPass(
                true, /*clearColor*/
                glm::vec4(0, 0, 0, 1) /*colorValue*/,
                true, /*clearDepth*/
                FLT_MAX /*depthValue*/);

            // Kick off draw. Note that it blocks the caller until drawcall is completed
            pRenderContext->DrawIndexed(3, 0);

            pRenderContext->EndRenderPass();

            const auto drawEnd = std::chrono::high_resolution_clock::now();
            auto renderTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(drawEnd - drawBegin);
            printf("Render time: %.3f ms\n", renderTime.count());
        }

        const auto presentBegin = std::chrono::high_resolution_clock::now();
        pDisplay->Present();
        const auto presentEnd = std::chrono::high_resolution_clock::now();
        auto presentTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(presentEnd - presentBegin);
        //printf("Display time: %.3f ms\n", presentTime.count());
    }

    pRenderContext->Destroy();
    delete pRenderContext;

    delete[] pColorBuffer;
    delete[] pDepthBuffer;
    delete pDisplay;

    return 0;
}

bool ParseCommandLine(int argc, char** ppArgv, RasterizerConfig* pConfig, Optional* pOptional)
{
    for (uint32_t i = 1; i < argc; i++)
    {
        if (!strcmp("-h", ppArgv[i]))
        {
            printf("-num_threads\t\t-> Set number of threads to execute pipeline stages in parallel\n");
            printf("-iteration_size\t\t-> Set max number of triangles to be processed per iteration\n");
            printf("-tile_size\t\t-> Set RT tile size, multiple of 8 up to 128\n");
            printf("-display_idx\t\t-> Index of SDL Renderer to be used for display\n");
            printf("-screen_width\t\t-> Screen width\n");
            printf("-screen_height\t\t-> Screen height\n");
            printf("-display_fullscreen\t\t-> Render to window in fullscreen mode\n");

            // Dry run
            return false;
        }
        else if (!strcmp("-num_threads", ppArgv[i]))
        {
            pConfig->m_NumPipelineThreads = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-iteration_size", ppArgv[i]))
        {
            pConfig->m_MaxDrawIterationSize = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-tile_size", ppArgv[i]))
        {
            pConfig->m_TileSize = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-display_idx", ppArgv[i]))
        {
            pOptional->m_SDLRendererIdx = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-screen_width", ppArgv[i]))
        {
            pOptional->m_ScreenWidth = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-screen_height", ppArgv[i]))
        {
            pOptional->m_ScreenHeight = atoi(ppArgv[++i]);
        }
        else if (!strcmp("-display_fullscreen", ppArgv[i]))
        {
            pOptional->m_DisplayFullscreen = atoi(ppArgv[++i]);
        }
    }

    return true;
}