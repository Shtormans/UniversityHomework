using Lab_1.Features.GameLoop.Field;
using Lab_1.Features.Input.Services;
using Lab_1.Features.Output;
using System.Drawing;

namespace Lab_1.Features.GameLoop
{
    internal class GameLoop : IGameLoop
    {
        private FieldContainer _fieldContainer;

        private readonly IInputService _inputService;
        private readonly IOutputService _outputService;

        public GameLoop(IInputService inputService, IOutputService outputService)
        {
            _inputService = inputService;
            _outputService = outputService;
        }

        public void RunGame()
        {
            Init();

            Run();
        }

        public void Run()
        {
            
        }

        public void Init()
        {
            InitField();
            InitCannon();
        }

        private void InitField()
        {
            while (true)
            {
                Size fieldSize = InputFieldSize();

                FieldCreationModel fieldCreationModel = new()
                {
                    BattleshipsAmount = GameLoopConstants.BattleShipsAmount,
                    BattleshipVariations = GameLoopConstants.BattleShipsVariations,
                    FieldSize = fieldSize
                };

                bool success = new FieldFactory().TryCreateField(fieldCreationModel, out _fieldContainer);

                if (success)
                {
                    _outputService.DisplatString(GameLoopConstants.Texts.FailedToCreateField);
                    _inputService.GetKeyDown();
                    return;
                }
            }
        }

        private void InitCannon()
        {
            int bulletsAmount = InputInt(GameLoopConstants.Texts.InputBulletsAmount);
        }

        private Size InputFieldSize()
        {
            int height = InputInt(GameLoopConstants.Texts.InputFieldHeight);
            int width = InputInt(GameLoopConstants.Texts.InputFieldWidth);

            return new Size(width, height);
        }

        private int InputInt(string inputText)
        {
            _outputService.DisplatString(inputText);

            while (true)
            {
                try
                {
                    return _inputService.GetInt();
                }
                catch (Exception)
                {
                    _outputService.DisplatString(GameLoopConstants.Texts.InputAgain);
                }
            }
        }
    }
}
