// Prj_Texto01 - Arquivo: Tela.cs
// Esse projeto exemplifica como mostrar textos na tela 
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;

namespace prj_Texto01
{
  // [---
  public partial class Tela : Form
  {
    
	// Para criação do dispositivo gráfico
	private Device device = null;     
    
	// Branco cor de fundo para nossa janela   
	private int cor_fundo = 0xFFFFFF;  
    
    // <b>
	// Objeto Font do DirectX para mostrar texto (mensagens)
    private Direct3D.Font dxfMensagem = null;

    // Objeto Font do DirectX para mostrar texto (titulos)
    private Direct3D.Font dxfTitulo = null;

    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;
	// </b>
	// ---] 

    public Tela()
    {
      // Qualquer configuração em algum componente, faça depois dessa função!
      // Pois a geração automática de código pode suprimir algo que você
      // fizer antes dela
      InitializeComponent();

      // Toda renderização deverá ocorrer dentro do evento onPaint()
      // Isso evita interferência estrangeira de processamento default
      // do sistema Windows
      this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);
    } // construtor

    // [---
	public void initGfx()
    {

      // Configuração dos parâmetros de apresentação
      PresentParameters pps = new PresentParameters();
      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;

      // Adaptador default, processamento no hardware, processamento de vértice no
      // software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);
		// <b>
      // Configuração das fontes para mostrar mensagens
      g_font = new System.Drawing.Font("Arial", 16.0f, FontStyle.Bold);
      dxfMensagem = new Direct3D.Font ( device, g_font);

      // Configuração das fontes para mostrar títulos
      g_font = new System.Drawing.Font("Arial", 36.0f, 
        FontStyle.Bold | FontStyle.Italic);
      dxfTitulo  = new Direct3D.Font(device, g_font);    
	  // </b>
  
    } // initGfx()
	// ---] 

	// [---
    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, cor_fundo, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui    
		// <b>
      // Mostra título do jogo
      MostrarTitulo(20,20,"SUPER NINJA GAIDEN",Color.Red);
      
      // Mostra mensagem na tela
      MostrarTextoCentralizado(320, 240, 
        "Pressione START para começar", Color.Blue);

      // Mostra título do jogo
      MostrarTitulo(20, 380, "By Gameprog", Color.YellowGreen);
	  // </b>
      
      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // render()
	// ---] 

    // [--- 
	// Mostra texto centralizado
	private void MostrarTextoCentralizado(int xpos, int ylin, string txt, Color font_cor)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);    
  
      // Mostra texto
      dxfMensagem.DrawText(null, txt, position,
        DrawTextFormat.NoClip | DrawTextFormat.Center, font_cor);
    }
	// ---] 

    // [--- 
	// Mostra texto com tamanho de fonte grande para títulos
    private void MostrarTitulo(int xpos, int ylin, string txt, Color font_cor)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfTitulo.DrawText(null, txt, position, DrawTextFormat.NoClip , font_cor);
    }
	// ---] 

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena
      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 
   
  } // fim da classe
} // fim do namespace
