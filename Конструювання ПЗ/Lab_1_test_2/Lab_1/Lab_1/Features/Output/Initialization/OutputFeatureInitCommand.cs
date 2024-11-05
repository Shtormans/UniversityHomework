using Lab_1.Domain.Abstract;
using Lab_1.Domain.Containers;

namespace Lab_1.Features.Output
{
    internal class OutputFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void InitFeature(DependencyContainer dependencyContainer)
        {
            IOutputService outputService = new OutputService();

            dependencyContainer.Add(outputService);
        }
    }
}
