#ifndef cubo_h
 #define cubo_h

#include <d3dx9.h>

class Cubo
{
public:
Cubo(IDirect3DDevice9  *device);
~Cubo();

bool desenhar(IDirect3DTexture9* tex);

private:
IDirect3DDevice9       *m_device;
IDirect3DVertexBuffer9 *m_vb;
IDirect3DIndexBuffer9  *m_ib;
};
#endif 