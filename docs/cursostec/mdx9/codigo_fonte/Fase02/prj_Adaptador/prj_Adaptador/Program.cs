// Projeto prj_Adaptador - Arquivo: Program.cs
// Este programa mostra como verificar os recursos oferecidos
// pela placa gráfica como modos de vídeo e outros aspectos.
// Produzido por www.gameprog.com.br
using System;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Adaptador
{
  class Program
  {
    static void Main(string[] args)
    {

       // Configura a janela de console
      config_janela("prj_Adaptador");

      // Exibe informações gerais da placa
      adaptador_exibirInfoGeral();

      // Exibe capacidades da placa gráfica
      adaptador_exibirCapacidades();

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
      Console.SetBufferSize(80, 600);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      Console.WriteLine("\n");
    } // config_janela() fim    


    // adaptador_exibirInfoGeral()
    // Exibe informações gerais e modo de vídeo do adaptador
    private static void adaptador_exibirInfoGeral()
    {

      // Obtém informações gerais do adaptador
      AdapterInformation placaVideo = Manager.Adapters[0];
      mostrar("Adaptador: " + placaVideo.Adapter.ToString());
      mostrar(placaVideo.Information.Description);
      mostrar(placaVideo.Information.DriverName);
      mostrar(placaVideo.Information.DriverVersion.ToString());


      mostrar("\n Modo de video atual: ");
      string info_modo_atual;
      // Acessa informação do modo de video corrente
      DisplayMode modo_atual = placaVideo.CurrentDisplayMode;
      // Formata a informação do modo de video e mostra-a
      info_modo_atual = string.Format("{0} x {1} - Formato:{2}\n",
        modo_atual.Width.ToString(),
        modo_atual.Height.ToString(),
        modo_atual.Format.ToString());
      mostrar(info_modo_atual);

      mostrar("\n Modos de video suportados: ");
      mostrar("--------------------------------------------------------");
      // Obtém informação dos outros modos de vídeos suportadores, formata
      // e exibe-a.
      DisplayModeEnumerator modos_video = placaVideo.SupportedDisplayModes;

      foreach (DisplayMode mdvideo in modos_video)
      {
        string info;
        info = string.Format("{0} x {1} -{2}",
          mdvideo.Width.ToString(),
          mdvideo.Width.ToString(),
          mdvideo.Format.ToString());
        mostrar(info);
      } //endfor each  

    } // adaptador_exibirInfoGeral().fim


    // Exibe centenas de capacidades gráficas que podem ou não
    // estarem disponíveis no adaptador gráfico default.
    private static void adaptador_exibirCapacidades()
    {
      mostrar("\n Capacidades do adaptador: ");
      mostrar("--------------------------------------------------------");
      Caps capacidades = Manager.GetDeviceCaps(0, DeviceType.Hardware);
      mostrar(capacidades.ToString());
    }// adaptador_exibirCapacidades()




    // mostra() mostras informação na tela
    private static void mostrar(object informacao)
    {
      // Geralmente Console.Writeline() chama ToString() do
      // objeto
      Console.WriteLine(" {0}", informacao);
    } // mostrar().fim

  } // fim da classe Program
} // fim do namespace prj_Adaptador
