using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Frame
{
    internal class FrameManager : GameManager
    {
        private List<GameManager> _gameManagers;

        public override void Init()
        {
            _gameManagers = new();
        }

        public override void Update()
        {
            foreach (GameManager gameManager in _gameManagers)
            {
                gameManager.Update();
            }
        }

        public void AddManager(GameManager gameManager)
        {
            _gameManagers.Add(gameManager);
        }
    }
}
