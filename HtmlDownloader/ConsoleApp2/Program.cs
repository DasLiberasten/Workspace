using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;

namespace ConsoleApplication5 //http://www.ntu.edu.sg/home/ehchua/programming/webprogramming/HTTP_Basics.html
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                MainAsync(args).Wait();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Source);
                Console.WriteLine(e.Message);
            }
        }

        static async Task MainAsync(string[] args)
        {
            int x;
            string code;
            bool flag = false;
            do
            {
                Console.WriteLine("1:Read HTML code");
                Console.WriteLine("2:Find all HTML links in ur HTML code");
                Console.WriteLine("3:reCursFunc");
                Console.WriteLine("4:Exit");
                x = int.Parse(Console.ReadLine());
                switch (x)
                {
                    case 1:
                        Console.WriteLine("write ur html code : ");
                        code = Console.ReadLine();
                        await LoadPages(code);
                        break;
                    case 2:
                        Console.WriteLine("write ur html code : ");
                        code = Console.ReadLine();
                        string strAllCode = await ReadHtml(code);
                        string strOnlyHTML = "";
                        int i = 0;
                        int index = -1;
                        while (strAllCode.IndexOf("http:") > -1)
                        {
                            index = strAllCode.IndexOf("http:");
                            //Console.WriteLine("pass 1 kp");
                            do
                            {
                                // Console.Write(strAllCode[strAllCode.IndexOf("http") + i]);
                                strOnlyHTML = strOnlyHTML + strAllCode[strAllCode.IndexOf("http:") + i];
                                i++;
                            } while (((strAllCode.IndexOf("http:") + i) <= (strAllCode.Length)) && (strAllCode[strAllCode.IndexOf("http:") + i] != ' ') && (strAllCode[strAllCode.IndexOf("http:") + i] != '"'));
                            //Console.WriteLine("pass 2 kp");
                            Console.WriteLine(strOnlyHTML);
                            //Console.WriteLine("pass 3 kp");
                            strOnlyHTML = "";
                            strAllCode = strAllCode.Insert(index + 1, "g");
                            i = 0;
                        }

                        break;
                    case 3:
                        Console.WriteLine("SAAAAASSSSAAAAAAAATTTTBBBBB");
                        break;
                    case 4:
                        Console.WriteLine("EXIT");
                        flag = true;
                        break;
                    default:
                        Console.WriteLine("Default case");
                        break;
                }
            } while (!flag);
        }

        static async Task LoadPages(string _code)
        {
            Console.WriteLine("Started loading pages...");
            HttpClient client = new HttpClient();
            var page1Task = client.GetAsync(_code);
            var page1 = await page1Task;
            var html1 = await page1.Content.ReadAsStringAsync();
            Console.WriteLine(html1);
        }
        static async Task<string> ReadHtml(string _code)
        {
            Console.WriteLine("Started loading pages...");
            HttpClient client = new HttpClient();
            var page1Task = client.GetAsync(_code);
            var page1 = await page1Task;
            return await page1.Content.ReadAsStringAsync();
        }
    }
}
