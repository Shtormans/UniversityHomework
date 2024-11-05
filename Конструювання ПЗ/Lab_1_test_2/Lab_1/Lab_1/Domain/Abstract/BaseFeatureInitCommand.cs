using Lab_1.Domain.Containers;

namespace Lab_1.Domain.Abstract
{
    internal abstract class BaseFeatureInitCommand
    {
        public abstract void InitFeature(DependencyContainer dependencyContainer);
    }
}
