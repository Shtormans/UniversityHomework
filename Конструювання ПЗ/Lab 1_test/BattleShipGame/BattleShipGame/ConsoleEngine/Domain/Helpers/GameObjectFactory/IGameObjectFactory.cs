using ConsoleEngine.Domain.Entities;

namespace ConsoleEngine.Domain.Helpers
{
    internal interface IGameObjectFactory
    {
        public GameObject Instantiate<T>() where T : GameObject;
        public GameObject Instantiate<T>(Transform parent) where T : GameObject;
    }
}
