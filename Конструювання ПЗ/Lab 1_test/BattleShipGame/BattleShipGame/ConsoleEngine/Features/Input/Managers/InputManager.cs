using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Input
{
    internal class InputManager : GameManager
    {
        private bool[] _calculationKeys;

        public bool[] EnteredKeys { get; private set; }

        public override void Init()
        {
            _calculationKeys = new bool[255];
            EnteredKeys = new bool[255];
        }

        public override void Update()
        {
            SwapArrays();
            ClearCalculationArray();
        }

        private void SwapArrays()
        {
            (_calculationKeys, EnteredKeys) = (EnteredKeys, _calculationKeys);
        }

        private void ClearCalculationArray()
        {
            Array.Clear(_calculationKeys);
        }
    }
}
