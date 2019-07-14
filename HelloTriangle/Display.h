#pragma once

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

// SDL is the underlying display facility used to present frames
// SDL_PIXELFORMAT_ARGB8888 is the pre-defined surface format
struct Display
{
    Display(uint8_t* pColorBuffer, int32_t rendererIdx, const uint32_t w, const uint32_t h, bool fullscreen, const char* pTitle);
    ~Display();

    /* Clear depth & frame buffers before re-draw */
    void ClearRenderTarget();

    // Render frame buffer to SDL render target
    void Present();

    SDL_Renderer*   m_pRenderer = nullptr;
    SDL_Window*     m_pWindow = nullptr;
    SDL_Texture*    m_pRenderTexture = nullptr;

    // Color buffer that SDL will use to present frame buffer content
    uint8_t*        m_pColorBuffer;
    uint32_t        m_Width;
    uint32_t        m_Height;
};