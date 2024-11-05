namespace Lab_1.Domain.Containers
{
    internal class DependencyContainer
    {
        private Dictionary<Type, object> _dependecies;

        public DependencyContainer()
        {
            _dependecies = new();
        }

        public void Add<T>(T instance) where T : class
        {
            _dependecies.Add(typeof(T), instance);
        }

        public T Get<T>() where T : class
        {
            return (_dependecies[typeof(T)] as T)!;
        }
    }
}
