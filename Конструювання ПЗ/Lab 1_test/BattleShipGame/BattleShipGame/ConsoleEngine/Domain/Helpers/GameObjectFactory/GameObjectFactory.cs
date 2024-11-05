using ConsoleEngine.Domain.Entities;
using ConsoleEngine.Features.GameLoop;

namespace ConsoleEngine.Domain.Helpers
{
    internal class GameObjectFactory : IGameObjectFactory
    {
        private readonly IClassFactory _classFactory;
        private readonly GameObjectsContainer _gameObjectsContainer;

        public GameObjectFactory(IClassFactory classFactory, GameObjectsContainer gameObjectsContainer)
        {
            _classFactory = classFactory;
            _gameObjectsContainer = gameObjectsContainer;
        }

        public GameObject Instantiate<T>() where T : GameObject
        {
            GameObject gameObject = _classFactory.Create<T>();

            _gameObjectsContainer.Add(gameObject);

            return gameObject;
        }

        public GameObject Instantiate<T>(Transform parent) where T : GameObject
        {
            GameObject gameObject = _classFactory.Create<T>();
            gameObject.Transform.SetParent(parent, true); 

            _gameObjectsContainer.Add(gameObject);

            return gameObject;
        }
    }
}
