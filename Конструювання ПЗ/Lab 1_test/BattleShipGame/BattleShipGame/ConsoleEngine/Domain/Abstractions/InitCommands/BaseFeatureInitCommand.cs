using ConsoleEngine.Domain.Helpers;

namespace ConsoleEngine.Domain.Abstractions
{
    internal abstract class BaseFeatureInitCommand
    {
        protected IClassFactory ClassFactory { get; }

        public abstract void BindDependencies();

        public virtual void InitManagers()
        {

        }

        public virtual void InitServices()
        {

        }

        public virtual void InitSystems()
        {

        }
    }
}
