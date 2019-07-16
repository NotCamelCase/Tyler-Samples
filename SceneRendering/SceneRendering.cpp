#include <Tyler/RenderContext.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Display.h"

#define CAM_MOVE_SPEED 5.f

using namespace tyler;

// Vertex layout
struct Vertex
{
    glm::vec3   m_Pos;
#if 1
    glm::vec3   m_Normal;
#else
    glm::vec2   m_TexCoords;
#endif
};

// Shader constants
struct Constants
{
    glm::mat4   m_ModelViewProj;
};

// Indexed mesh
struct Mesh
{
    // Offset into the global index buffer
    uint32_t    m_IdxOffset = 0u;

    // How many indices this mesh contains. Number of triangles therefore equals (m_IdxCount / 3)
    uint32_t    m_IdxCount = 0u;
};

// Optional args to be passed to app
struct Optional
{
    const char* m_OBJName = "./assets/sponza.obj";
    int32_t     m_SDLRendererIdx = 1;
    uint32_t    m_ScreenWidth = 1280;
    uint32_t    m_ScreenHeight = 768u;
    bool        m_DisplayFullscreen = false;
    bool        m_RunBenchmark = false;
    uint32_t    m_NumFramesOffline = 250u;
};

struct TestParams
{
    glm::vec3   m_EyePos;
    glm::vec3   m_LookAtPos;
};

TestParams  g_SponzaScene =
{
    glm::vec3(943.f, 304.f, 5.f), // Eye pos
    glm::vec3(0, 0, 0)            // LookAt pos
};

TestParams  g_SibenikScene =
{
    glm::vec3(-36.f, -10.f, 1.f), // Eye pos
    glm::vec3(80.f, -13.f, 0.f)  // LookAt pos
};

TestParams  g_RungholtScene =
{
    glm::vec3(298.000, 299.000, 300.000), // Eye pos
    glm::vec3(-5.000, 0.000, 0.000)      // LookAt pos
};

TestParams  g_DefaultScene =
{
    glm::vec3(3, 4, 5), // Eye pos
    glm::vec3(0, 0, 0)  // LookAt pos
};

bool ParseCommandLine(int argc, char** ppArgv, RasterizerConfig* pConfig, Optional* pOptional, TestParams* pParams);

void OutputFrame(uint8_t* pColorBuffer, const char* pFilename, uint32_t width, uint32_t height)
{
    FILE* pFile = nullptr;
    fopen_s(&pFile, pFilename, "w");
    fprintf(pFile, "P3\n%d %d\n%d\n ", width, height, 255);
    for (auto i = 0; i < width * height * 4; i += 4)
    {
        // Write out color values clamped to [0, 255] 
        uint8_t r = pColorBuffer[i + 0];
        uint8_t g = pColorBuffer[i + 1];
        uint8_t b = pColorBuffer[i + 2];
        fprintf(pFile, "%d %d %d ", r, g, b);
    }
    fclose(pFile);
}

void InitializeSceneObjects(const char* fileName, std::vector<Mesh>& meshBuffer, std::vector<Vertex>& vertexBuffer, std::vector<uint32_t>& indexBuffer)
{
    printf("Loading %s...\n", fileName);

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err = "";

    bool ret = tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, &err, fileName, "./assets", true /*triangulate*/, true /*default_vcols_fallback*/);
    if (ret)
    {
        printf("\tNumber of vertices  = %d\n", static_cast<int>((attribs.vertices.size()) / 3));
        printf("\tNumber of normals   = %d\n", static_cast<int>((attribs.normals.size()) / 3));
        printf("\tNumber of texcoords = %d\n", static_cast<int>((attribs.texcoords.size()) / 2));
        printf("\tNumber of materials = %d\n", static_cast<int>(materials.size()));
        printf("\tNumber of shapes    = %d\n", static_cast<int>(shapes.size()));

        // Process vertices
        {
            // POD of indices of vertex data provided by tinyobjloader, used to map unique vertex data to indexed primitive
            struct IndexedPrimitive
            {
                uint32_t PosIdx;
                uint32_t NormalIdx;

                bool operator<(const IndexedPrimitive& other) const
                {
                    return memcmp(this, &other, sizeof(IndexedPrimitive)) > 0;
                }
            };

            std::map<IndexedPrimitive, uint32_t> indexedPrims;
            for (size_t s = 0; s < shapes.size(); s++)
            {
                const tinyobj::shape_t& shape = shapes[s];

                size_t meshIdxBase = indexBuffer.size();
                for (size_t i = 0; i < shape.mesh.indices.size(); i++)
                {
                    auto index = shape.mesh.indices[i];

                    // Fetch indices to construct an IndexedPrimitive to first look up existing unique vertices
                    int vtxIdx = index.vertex_index;
                    assert(vtxIdx != -1);

                    bool hasNormals = index.normal_index != -1;

                    int normalIdx = index.normal_index;
                    int uvIdx = index.texcoord_index;

                    IndexedPrimitive prim;
                    prim.PosIdx = vtxIdx;
                    prim.NormalIdx = hasNormals ? normalIdx : UINT32_MAX;

                    auto res = indexedPrims.find(prim);
                    if (res != indexedPrims.end())
                    {
                        // Vertex is already defined in terms of POS/NORMAL/UV indices, just append index data to index buffer
                        indexBuffer.push_back(res->second);
                    }
                    else
                    {
                        // New unique vertex found, get vertex data and append it to vertex buffer and update indexed primitives
                        auto newIdx = vertexBuffer.size();
                        indexedPrims[prim] = newIdx;
                        indexBuffer.push_back(newIdx);

                        auto vx = attribs.vertices[3 * index.vertex_index];
                        auto vy = attribs.vertices[3 * index.vertex_index + 1];
                        auto vz = attribs.vertices[3 * index.vertex_index + 2];

                        glm::vec3 pos(vx, vy, vz);

                        glm::vec3 normal(0.f);
                        if (hasNormals)
                        {
                            auto nx = attribs.normals[3 * index.normal_index];
                            auto ny = attribs.normals[3 * index.normal_index + 1];
                            auto nz = attribs.normals[3 * index.normal_index + 2];

                            normal.x = nx;
                            normal.y = ny;
                            normal.z = nz;
                        }

                        Vertex uniqueVertex = { pos, normal };
                        vertexBuffer.push_back(uniqueVertex);
                    }
                }

                // Push new mesh to be rendered in the scene 
                Mesh mesh;
                mesh.m_IdxOffset = meshIdxBase;
                mesh.m_IdxCount = shape.mesh.indices.size();

                meshBuffer.push_back(mesh);
            }
        }

        printf("\tNumber of triangles = %d\n", static_cast<int>(indexBuffer.size() / 3u));
    }
    else
    {
        printf("ERROR: %s\n", err.c_str());
        assert(false && "Failed to load .OBJ file, check file paths!");
    }
}

glm::vec4 VS(VertexInput* pVertexInput, VertexAttributes* pVertexAtributes, ConstantBuffer* pConstantBuffer)
{
    Vertex& vertex = *reinterpret_cast<Vertex*>(pVertexInput);
    Constants& cb = *reinterpret_cast<Constants*>(pConstantBuffer);

#if 1 // Pass normal to be interpolated
    pVertexAtributes->m_Attributes3[0] = vertex.m_Normal;
#else // Pass texture coordinates to be interpolated
    pVertexAtributes->m_Attributes2[0] = vertex.m_TexCoords;
#endif

    return (cb.m_ModelViewProj * glm::vec4(vertex.m_Pos, 1.f));
}

void FS(InterpolatedAttributes* pVertexAttributes, ConstantBuffer* pConstantBuffer, FragmentOutput* pFragmentOut)
{
#if 1 // Render scaled normals
    __m128 sseX = _mm_mul_ps(pVertexAttributes->m_Vec3Attributes[0].m_SSEX, _mm_set_ps1(0.5f)); // x = x * 0.5
    __m128 sseY = _mm_mul_ps(pVertexAttributes->m_Vec3Attributes[0].m_SSEY, _mm_set_ps1(0.5f)); // y = y * 0.5
    __m128 sseZ = _mm_mul_ps(pVertexAttributes->m_Vec3Attributes[0].m_SSEZ, _mm_set_ps1(0.5f)); // z = z * 0.5

    sseX = _mm_add_ps(sseX, _mm_set_ps1(0.5f)); // x = x * 0.5 + 0.5
    sseY = _mm_add_ps(sseY, _mm_set_ps1(0.5f)); // y = y * 0.5 + 0.5
    sseZ = _mm_add_ps(sseZ, _mm_set_ps1(0.5f)); // z = z * 0.5 + 0.5

    // Ugly hack to transpose RRRR to interleaved RGBA pixel values

    // Sample #0
    pFragmentOut->m_FragmentColors[0].m128_f32[0] = sseX.m128_f32[0];
    pFragmentOut->m_FragmentColors[0].m128_f32[1] = sseY.m128_f32[0];
    pFragmentOut->m_FragmentColors[0].m128_f32[2] = sseZ.m128_f32[0];
    pFragmentOut->m_FragmentColors[0].m128_f32[3] = 1.f;

    // Sample #1
    pFragmentOut->m_FragmentColors[1].m128_f32[0] = sseX.m128_f32[1];
    pFragmentOut->m_FragmentColors[1].m128_f32[1] = sseY.m128_f32[1];
    pFragmentOut->m_FragmentColors[1].m128_f32[2] = sseZ.m128_f32[1];
    pFragmentOut->m_FragmentColors[1].m128_f32[3] = 1.f;

    // Sample #2
    pFragmentOut->m_FragmentColors[2].m128_f32[0] = sseX.m128_f32[2];
    pFragmentOut->m_FragmentColors[2].m128_f32[1] = sseY.m128_f32[2];
    pFragmentOut->m_FragmentColors[2].m128_f32[2] = sseZ.m128_f32[2];
    pFragmentOut->m_FragmentColors[2].m128_f32[3] = 1.f;

    // Sample #3
    pFragmentOut->m_FragmentColors[3].m128_f32[0] = sseX.m128_f32[3];
    pFragmentOut->m_FragmentColors[3].m128_f32[1] = sseY.m128_f32[3];
    pFragmentOut->m_FragmentColors[3].m128_f32[2] = sseZ.m128_f32[3];
    pFragmentOut->m_FragmentColors[3].m128_f32[3] = 1.f;
#else
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[0]), _mm_set1_ps(1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[1]), _mm_set1_ps(1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[2]), _mm_set1_ps(1.f));
    _mm_store_ps(reinterpret_cast<float*>(&pFragmentOut->m_FragmentColors[3]), _mm_set1_ps(1.f));
#endif
}

int main(int argc, char** ppArgv)
{
    RasterizerConfig config = {};
    Optional opt = {};
    TestParams testParams = g_SponzaScene;
    if (!ParseCommandLine(argc, ppArgv, &config, &opt, &testParams)) return 0;

    RenderContext* pRenderContext = new RenderContext(config);
    if (!pRenderContext->Initialize())
    {
        assert(false && "RenderContext failed to initialize!");

        delete pRenderContext;
    }

    // Allocate color & depth buffers
    uint8_t* pColorBuffer = new uint8_t[opt.m_ScreenWidth * opt.m_ScreenHeight * 4]; // Color buffer format == R8G8B8A8_UNORM
    float* pDepthBuffer = new float[opt.m_ScreenWidth * opt.m_ScreenHeight]; // Depth buffer format == D32_FLOAT

    Display* pDisplay = nullptr;
    if (!opt.m_RunBenchmark)
    {
        // Use SDL to display a window
        pDisplay = new Display(pColorBuffer, opt.m_SDLRendererIdx, opt.m_ScreenWidth, opt.m_ScreenHeight, opt.m_DisplayFullscreen, "Scene Rendering");
    }

    // Set up main FBO
    Framebuffer fbo = {};
    fbo.m_pColorBuffer = pColorBuffer;
    fbo.m_pDepthBuffer = pDepthBuffer;
    fbo.m_Width = opt.m_ScreenWidth;
    fbo.m_Height = opt.m_ScreenHeight;

    // Single vec3 attribute is used to pass vertex normal VS -> FS
    ShaderMetadata metadata = { 0, 1 /*vertex normal*/, 0 };

    float nearPlane = 0.1f;
    float farPlane = 5000.f;

    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 view = glm::lookAt(testParams.m_EyePos, testParams.m_LookAtPos, glm::vec3(0, 1, 0));
    glm::mat4 proj = glm::perspective(
        glm::radians(60.f),
        static_cast<float>(opt.m_ScreenWidth) / static_cast<float>(opt.m_ScreenHeight),
        nearPlane,
        farPlane);
    proj[1][1] *= -1.f;

    // Emulate passing of constants data to shaders
    Constants cb;
    cb.m_ModelViewProj = proj * view * model;

    // We will have single index and vertex buffer to draw indexed mesh
    std::vector<Vertex> vertexBuffer;
    std::vector<uint32_t> indexBuffer;

    // Store data of all scene objects to be drawn
    std::vector<Mesh> objects;

    InitializeSceneObjects(opt.m_OBJName, objects, vertexBuffer, indexBuffer);

    // Bind FBO to be used in subsequent render pass once
    pRenderContext->BindFramebuffer(&fbo);

    // Bind VBO and set buffer stride
    pRenderContext->BindVertexBuffer(vertexBuffer.data(), sizeof(Vertex));
    // Bind IBO
    pRenderContext->BindIndexBuffer(indexBuffer.data());

    // Bind shader constants
    pRenderContext->BindConstantBuffer(&cb);

    //TODO: Bind shader, constant buffer, texture(s)
    pRenderContext->BindShaders(VS, FS, metadata);

    if (opt.m_RunBenchmark)
    {
        double minDelta = std::numeric_limits<double>::max();
        double maxDelta = 0.0;

        const auto benchBegin = std::chrono::high_resolution_clock::now();

        for (uint32_t numFrames = 0; numFrames < opt.m_NumFramesOffline; numFrames++)
        {
            // Bind FBO to be used in subsequent render pass once
            pRenderContext->BindFramebuffer(&fbo);

            // Clear RT
            pRenderContext->BeginRenderPass(
                true, /*clearColor*/
                glm::vec4(0, 0, 0, 1) /*colorValue*/,
                true, /*clearDepth*/
                FLT_MAX /*depthValue*/);

            // Bind VBO and set buffer stride
            pRenderContext->BindVertexBuffer(vertexBuffer.data(), sizeof(Vertex));
            // Bind IBO
            pRenderContext->BindIndexBuffer(indexBuffer.data());

            //TODO: Bind shader, constant buffer, texture(s)
            pRenderContext->BindShaders(VS, FS, metadata);

            const auto drawBegin = std::chrono::high_resolution_clock::now();

            // Draw meshes
            for (uint32_t obj = 0; obj < objects.size(); obj++)
            {
                Mesh& mesh = objects[obj];

                // Kick off draw. Note that it blocks callee until drawcall is completed
                pRenderContext->DrawIndexed(mesh.m_IdxCount, mesh.m_IdxOffset);
            }

            pRenderContext->EndRenderPass();

            const auto drawEnd = std::chrono::high_resolution_clock::now();
            auto renderTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(drawEnd - drawBegin);
            printf("Frame %d time: %.3f ms\n", numFrames, renderTime.count());

            double deltaTime = renderTime.count();
            minDelta = glm::min(minDelta, deltaTime);
            maxDelta = glm::max(maxDelta, deltaTime);
        }

        const auto benchEnd = std::chrono::high_resolution_clock::now();
        auto benchTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(benchEnd - benchBegin);

        printf("Min time:       %.3f\n", minDelta);
        printf("Max time:       %.3f\n", maxDelta);
        printf("Average time:   %.3f\n", benchTime.count() / opt.m_NumFramesOffline);

        // Output single-frame result
        OutputFrame(pColorBuffer, "SceneRendering.ppm", opt.m_ScreenWidth, opt.m_ScreenHeight);
    }
    else
    {
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
                    case SDL_SCANCODE_A:
                        testParams.m_EyePos += CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_D:
                        testParams.m_EyePos.x -= CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_W:
                        testParams.m_EyePos.z += CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_S:
                        testParams.m_EyePos.z -= CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_E:
                        testParams.m_EyePos.y += CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_Q:
                        testParams.m_EyePos.y -= CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_UP:
                        testParams.m_LookAtPos.y += CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_DOWN:
                        testParams.m_LookAtPos.y -= CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_LEFT:
                        testParams.m_LookAtPos.x -= CAM_MOVE_SPEED;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        testParams.m_LookAtPos.x += CAM_MOVE_SPEED;
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

                // Draw meshes
                for (uint32_t obj = 0; obj < objects.size(); obj++)
                {
                    Mesh& mesh = objects[obj];

                    view = glm::lookAt(testParams.m_EyePos, testParams.m_LookAtPos, glm::vec3(0, 1, 0));
                    //model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 1, 0));
                    cb.m_ModelViewProj = proj * view * model;

                    // Kick off draw. Note that it blocks callee until drawcall is completed
                    pRenderContext->DrawIndexed(mesh.m_IdxCount, mesh.m_IdxOffset);
                }

                pRenderContext->EndRenderPass();

                //printf("Eye pos:    (%.3f, %.3f, %.3f)\n", testParams.m_EyePos.x, testParams.m_EyePos.y, testParams.m_EyePos.z);
                //printf("LookAt pos: (%.3f, %.3f, %.3f)\n", testParams.m_LookAtPos.x, testParams.m_LookAtPos.y, testParams.m_LookAtPos.z);

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
    }

    pRenderContext->Destroy();
    delete pRenderContext;

    delete[] pColorBuffer;
    delete[] pDepthBuffer;
    delete pDisplay;

    return 0;
}

bool ParseCommandLine(int argc, char** ppArgv, RasterizerConfig* pConfig, Optional* pOptional, TestParams* pParams)
{
    for (uint32_t i = 1; i < argc; i++)
    {
        if (!strcmp("-h", ppArgv[i]))
        {
            printf("-num_threads\t\t-> Set number of threads to execute pipeline stages in parallel\n");
            printf("-iteration_size\t\t-> Set max number of triangles to be processed per iteration\n");
            printf("-tile_size\t\t-> Set RT tile size, multiple of 8 up to 128\n");
            printf("-display_idx\t\t-> Index of SDL Renderer to be used for display\n");
            printf("-obj_name\t\t-> Name of .OBJ scene file to be rendered\n");
            printf("-screen_width\t\t-> Screen width\n");
            printf("-screen_height\t\t-> Screen height\n");
            printf("-display_fullscreen\t\t-> Render to window in fullscreen mode\n");
            printf("-run_benchmark\t\t-> Render num_frames frames for performance benchmarking\n");
            printf("-num_frames\t\t-> Number of frames to be rendered in benchmark\n");

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
        else if (!strcmp("-obj_name", ppArgv[i]))
        {
            pOptional->m_OBJName = ppArgv[++i];

            if (std::string(pOptional->m_OBJName).find("sibenik") != std::string::npos)
            {
                *pParams = g_SibenikScene;
            }
            else if (std::string(pOptional->m_OBJName).find("sponza") != std::string::npos)
            {
                *pParams = g_SponzaScene;
            }
            else if (std::string(pOptional->m_OBJName).find("rungholt") != std::string::npos)
            {
                *pParams = g_RungholtScene;
            }
            else
            {
                *pParams = g_DefaultScene;
            }
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
        else if (!strcmp("-run_benchmark", ppArgv[i]))
        {
            pOptional->m_RunBenchmark = true;
        }
        else if (!strcmp("-num_frames", ppArgv[i]))
        {
            pOptional->m_NumFramesOffline = atoi(ppArgv[++i]);
        }
    }

    return true;
}