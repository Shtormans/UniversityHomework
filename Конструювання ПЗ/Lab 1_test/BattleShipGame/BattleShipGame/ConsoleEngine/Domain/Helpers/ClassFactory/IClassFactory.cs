using System.Collections;

namespace ConsoleEngine.Domain.Helpers
{
    public interface IClassFactory
    {
        public void Bind<TImplementation>() where TImplementation : class;
        public void Bind<TInterface, TImplementation>() 
            where TInterface : class 
            where TImplementation : class, TInterface;

        public T Create<T>(IEnumerable<object> extraData = null) where T : class;
        public T Resolve<T>() where T : class;
    }
}
