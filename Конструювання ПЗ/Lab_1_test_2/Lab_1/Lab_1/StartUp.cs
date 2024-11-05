using Lab_1.Domain.Abstract;
using Lab_1.Domain.Containers;
using Lab_1.Features.GameLoop;
using Lab_1.Features.Input;
using Lab_1.Features.Output;

namespace Lab_1
{
    internal class StartUp
    {
        private DependencyContainer _dependencyContainer;

        public void Run()
        {
            InitDependencies();

            _dependencyContainer.Get<IGameLoop>().RunGame();
        }

        private void InitDependencies()
        {
            _dependencyContainer = new();

            AddFeature(new InputFeatureInitCommand());
            AddFeature(new OutputFeatureInitCommand());
            AddFeature(new GameLoopFeatureInitCommand());
        }

        private void AddFeature(BaseFeatureInitCommand featureInitCommand)
        {
            featureInitCommand.InitFeature(_dependencyContainer);
        }
    }
}
