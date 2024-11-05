using ConsoleEngine.Domain.Abstractions;
using ConsoleEngine.Domain.Helpers;
using ConsoleEngine.Features.Frame;
using ConsoleEngine.Features.Input;
using ConsoleEngine.Features.Output;
using ConsoleEngine.Features.Time;

namespace ConsoleEngine.Features.GameLoop.Containers
{
    internal class FeaturesContainer
    {
        private List<BaseFeatureInitCommand> _featureInitCommands = new();

        private readonly IClassFactory _classFactory;

        public FeaturesContainer(IClassFactory classFactory)
        {
            _classFactory = classFactory;
        }

        public void Init()
        {
            AddFeatures();
            InitFeatures();
        }

        private void AddFeatures()
        {
            AddFeature<FrameFeatureInitCommand>();

            AddFeature<TimeFeatureInitCommand>();
            AddFeature<InputFeatureInitCommand>();
            AddFeature<OutputFeatureInitCommand>();
        }

        private void InitFeatures()
        {
            foreach (BaseFeatureInitCommand initCommand in _featureInitCommands)
            {
                initCommand.BindDependencies();

                initCommand.InitManagers();
                initCommand.InitServices();
                initCommand.InitSystems();
            }
        }

        private void AddFeature<T>() where T : BaseFeatureInitCommand
        {
            BaseFeatureInitCommand initCommand = CreateFeature<T>();

            _featureInitCommands.Add(initCommand);
        }

        private T CreateFeature<T>() where T : BaseFeatureInitCommand
        {
            return _classFactory.Create<T>();
        }
    }
}
