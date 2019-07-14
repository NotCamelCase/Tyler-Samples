#include "Display.h"

Display::Display(uint8_t* pColorBuffer, int32_t rendererIdx, const uint32_t w, const uint32_t h, bool fullscreen, const char* pTitle)
    :
    m_pColorBuffer(pColorBuffer),
    m_Width(w),
    m_Height(h)
{
    SDL_Init(SDL_INIT_VIDEO);

    m_pWindow = SDL_CreateWindow(pTitle,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_Width,
        m_Height,
        SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

    m_pRenderer = SDL_CreateRenderer(m_pWindow, rendererIdx, SDL_RENDERER_ACCELERATED);

    SDL_RendererInfo info;
    SDL_GetRendererInfo(m_pRenderer, &info);
    printf("Renderer name: %s\n", info.name);
    printf("Texture formats: \n");
    for (uint32_t i = 0; i < info.num_texture_formats; i++)
    {
        printf("\t%s\n", SDL_GetPixelFormatName(info.texture_formats[i]));
    }

    //TODO: SDL_PIXELFORMAT_ABGR8888 is okay?!
    m_pRenderTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, m_Width, m_Height);
}

Display::~Display()
{
    SDL_DestroyTexture(m_pRenderTexture);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}

void Display::ClearRenderTarget()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_pRenderer);
}

void Display::Present()
{
    SDL_UpdateTexture(m_pRenderTexture, nullptr, m_pColorBuffer, m_Width * 4);

    SDL_RenderCopy(m_pRenderer, m_pRenderTexture, nullptr, nullptr);
    SDL_RenderPresent(m_pRenderer);
}