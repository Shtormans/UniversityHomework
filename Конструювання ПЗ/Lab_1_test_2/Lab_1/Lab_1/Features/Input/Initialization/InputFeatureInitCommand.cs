using Lab_1.Domain.Abstract;
using Lab_1.Domain.Containers;
using Lab_1.Features.Input.Services;

namespace Lab_1.Features.Input
{
    internal class InputFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void InitFeature(DependencyContainer dependencyContainer)
        {
            InputService inputService = new();

            dependencyContainer.Add<IInputService>(inputService);
        }
    }
}
