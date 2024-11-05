namespace ConsoleEngine.Domain.Helpers
{
    internal class ClassFactory : IClassFactory
    {
        public void Bind<TImplementation>() where TImplementation : class
        {
            throw new NotImplementedException();
        }

        public void Bind<TInterface, TImplementation>()
            where TInterface : class
            where TImplementation : class, TInterface
        {
            throw new NotImplementedException();
        }

        public T Create<T>(IEnumerable<object> extraData) where T : class
        {
            throw new NotImplementedException();
        }

        public T Resolve<T>() where T : class
        {
            throw new NotImplementedException();
        }
    }
}
