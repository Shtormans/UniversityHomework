using ConsoleEngine.Domain.Entities;

namespace ConsoleEngine.Features.GameLoop
{
    internal class GameObjectsContainer
    {
        private List<GameObject> gameObjects = new();

        public void Add(GameObject gameObject)
        {
            gameObjects.Add(gameObject);
        }
    }
}
