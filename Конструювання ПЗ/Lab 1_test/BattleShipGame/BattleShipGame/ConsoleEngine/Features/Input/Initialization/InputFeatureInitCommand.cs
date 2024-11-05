using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Input
{
    internal class InputFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void BindDependencies()
        {
            ClassFactory.Bind<InputManager>();

            ClassFactory.Bind<IInputService, InputService>();
        }

        public override void InitManagers()
        {
            ClassFactory.Resolve<InputManager>().Init();
        }

        public override void InitServices()
        {
            ClassFactory.Resolve<IInputService>().Init();
        }
    }
}
