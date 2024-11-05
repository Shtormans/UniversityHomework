using ConsoleEngine.Domain.Abstractions;
using ConsoleEngine.Domain.Helpers;

namespace ConsoleEngine.Domain.Entities
{
    public abstract class GameObject
    {
        private List<Component> _components = new();

        private readonly IClassFactory _classFactory;

        public GameObject(IClassFactory classFactory)
        {
            _classFactory = classFactory;
        }

        public Transform Transform { get; private set; }

        public virtual void Init()
        {
            AddTransform();
        }

        public T GetComponent<T>() where T : Component
        {
            return (T)_components.FirstOrDefault(c => c is T);
        }

        public void AddComponent<T>() where T : Component
        {
            Component component = CreateComponent<T>();

            _components.Add(component);
        }

        private Component CreateComponent<T>() where T : Component
        {
            return _classFactory.Create<T>();
        }

        private void AddTransform()
        {
            Transform = new();
        }
    }
}
