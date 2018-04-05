// Projeto prj_StringBuilder
// Este programa mostrar como utilizar a classe StringBuilder
using System;
using System.Text;

namespace prj_StringBuilder
{
    class Program
    {


        static void Main(string[] args)
        {

            config_janela("prj_StringBuilder");

            // Variáveis para construir uma página de Internet
            string titulo = "Curso_C#_fase_";
            int capitulo = 14;
            int topico = 2;

            string topo = "<html>";
            string rodape = "</body></html>\n\n";
            
            // Define um objeto StringBuilder
            StringBuilder sb_html;
            
            // Inicializa o objeto com a string topo e capacidade máxima
            sb_html = new StringBuilder(topo, 30000);
            
            // Adiciona texto no cabeçalho
            sb_html.Append("<head>\n");
            
            // Adiciona título da página
            sb_html.AppendFormat("<title>{0}{1}-{2}</title>\n", 
                titulo, capitulo, topico);
              
            // Fecha cabeçalho e abre corpo
            sb_html.AppendLine("</head><body>");
            
            // Adiciona conteúdo do corpo
            sb_html.AppendLine(" Produzido na escola Gameprog");
                        
            // Fecha o rodapé da página
            sb_html.AppendLine(rodape);


            // Exibe objeto
            Console.WriteLine(sb_html);

            // Modifica objeto
            sb_html.Replace("#", "Sharp");           
           
            // Exibe objeto
            Console.WriteLine(sb_html);
            Console.WriteLine("Tamanho:{0} Capacidade:{1}", 
                sb_html.Length, sb_html.Capacity);

            Console.Read();

        } // main() fim

        // Método para configurar a janela
        private static void config_janela(string titulo)
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = titulo;
            Console.SetBufferSize(80, 25);
            Console.SetWindowSize(80, 25);
            Console.Clear();
            Console.Write("\n");
        } // config_janela() fim    

    } // fim da classe Program
} // fim do namespace prj_StringBuilder