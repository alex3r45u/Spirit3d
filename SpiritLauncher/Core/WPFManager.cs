
using System.Windows.Navigation;
using Application = System.Windows.Application;
namespace SpiritLauncher.Core
{
    public class WPFManager
    {
        public static void NavigateToPage(string pageUri)
        {
            NavigationService nav = (Application.Current.MainWindow as MainWindow).RootFrame.NavigationService;
            nav.Navigate(new System.Uri(pageUri, System.UriKind.RelativeOrAbsolute));
        }

        public static void NavigateToPage(System.Uri pageUri)
        {
            NavigationService nav = (Application.Current.MainWindow as MainWindow).RootFrame.NavigationService;
            nav.Navigate(pageUri);
        }
    }
}
