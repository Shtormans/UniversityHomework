using Lab_1.Domain.Abstract;
using Lab_1.Domain.Containers;
using Lab_1.Features.Input.Services;
using Lab_1.Features.Output;

namespace Lab_1.Features.GameLoop
{
    internal class GameLoopFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void InitFeature(DependencyContainer dependencyContainer)
        {
            IInputService inputService = dependencyContainer.Get<IInputService>();
            IOutputService outputService = dependencyContainer.Get<IOutputService>();

            GameLoop gameLoop = new GameLoop(inputService, outputService);

            gameLoop.Init();
        }
    }
}
