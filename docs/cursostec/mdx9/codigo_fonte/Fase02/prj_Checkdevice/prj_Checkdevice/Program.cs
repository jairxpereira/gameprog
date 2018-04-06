// Projeto prj_verificarDispositivo - Arquivo: Program.cs
// Este programa mostra como verificar a presença de recursos
// particulares como formatos de vídeo e outros aspectos.
// Produzido por www.gameprog.com.br
using System;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_verificarDispositivo
{
  class Program
  {
    static void Main(string[] args)
    {
      // Configura a janela de console
      config_janela("prj_verificarDispositivo");

      // Variáveis de trabalho
      int     erro_info   = 0;      // Informação extra sobre erro
      string  mensagem    = null;   // mensagem ao usuário
      bool    sucesso     = false;  // Confirmação de sucesso ou não

      // Verificação de formato de vídeo e de backfuffer tela cheia (fullscreen)
      // Teste outros formatos
      sucesso = verificarDispositivo(Format.X8R8G8B8, 
        Format.X8R8G8B8 , out erro_info);

      if (sucesso)
        mensagem = String.Format("Ok - Formato de video\\backbuffer confirmada: {0}", 
          erro_info);
      else
        mensagem = String.Format(":-( Formato de video\\backbuffer indisponível: {0}", 
          erro_info);

      mostrar(mensagem);
      ResultCode res = (ResultCode)erro_info;
      mostrar( "Legenda: " + res.ToString());

      // Verificação de suporte aos shaders
      sucesso = verificarShaderSuporte(new Version(1, 1));
      if (sucesso) mostrar ( "PixelShader & VertexShader 1.1 Ok");
      
      sucesso = verificarShaderSuporte(new Version(2, 0));
      if (sucesso) mostrar ( "PixelShader & VertexShader 2.0 Ok");
      
      sucesso = verificarShaderSuporte(new Version(3, 0));
      if (sucesso) mostrar ( "PixelShader & VertexShader 3.0 Ok");

      if (!sucesso) mostrar("\n :-( Suporte fraco ou inexistente aos Shaders");
      if (!sucesso) mostrarVersaoShaders();

      // Aguarda a leitura da tela
      Console.Read();      

    } // main() fim

    // Método para configurar a janela
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      Console.WriteLine("\n");
    } // config_janela() fim    


    // mostra() mostras informação na tela
    private static void mostrar(object informacao)
    {
      // Geralmente Console.Writeline() chama ToString() do
      // objeto
      Console.WriteLine(" {0}", informacao);
    } // mostrar().fim


    // verificarDispositivo() Verifica possibilidade de configuração 
    // do dispositivo
    private static bool verificarDispositivo(Format video_formato, 
      Format backbuffer_formato, out int erro_info)
    {
      // Resultado
      bool res = false;
      
      // Aplicação vai rodar com o sem janela(false)
      bool app_janelada = false;
      
      // Coleta informações do adaptador default
      AdapterInformation info = Manager.Adapters.Default;      

      // Verifica se o dispositivo pode ser usado no adaptador default 
      // com a superfície dada
      res = Manager.CheckDeviceType(info.Adapter, DeviceType.Hardware, 
        video_formato, backbuffer_formato,
        app_janelada, out erro_info);

      // Além de res, HRESULT é passado de volta em erro_info
      return res;
    } // verificarDispositivo().fim

    
    // ShaderSuporte() - Verifica suporte aos shaders
    private static  bool verificarShaderSuporte( Version ver)
    {      
      // Faz leitura das capacidades do dispositivo
      Caps caps = Manager.GetDeviceCaps(0, DeviceType.Hardware);  

      // Verifica suporte conjunto aos Shaders
      if ((caps.VertexShaderVersion >= ver) && (caps.PixelShaderVersion >= ver))
      {
        return true;
      } // endif

      return false;
    } // ShaderSuporte().fim

    // mostrarVersaoShaders() - Mostrar versão dos Shaders
    private static void  mostrarVersaoShaders()
    {
      // Faz leitura das capacidades do dispositivo
      Caps caps = Manager.GetDeviceCaps(0, DeviceType.Hardware);

      mostrar("VertexShader: " + caps.VertexShaderVersion.ToString());
      mostrar(" PixelShader: " + caps.PixelShaderVersion.ToString());
    } // mostrarVersaoShaders().fim

  } // fim da classe Program
} // fim do namespace prj_Adaptador
