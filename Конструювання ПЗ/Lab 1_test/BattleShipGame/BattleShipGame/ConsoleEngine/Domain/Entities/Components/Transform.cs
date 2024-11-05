using ConsoleEngine.Domain.Abstractions;
using ConsoleEngine.Domain.ValueObjects;
using System.Drawing;

namespace ConsoleEngine.Domain.Entities
{
    public class Transform : Component
    {
        private Vector2 _position;
        private Vector2 _pivot;

        public Vector2 Position
        {
            get => _position;
            set => _position = value;
        }

        public Vector2 LocalPosition
        {
            get
            {
                Vector2 localPosition = _position;

                if (Parent is not null)
                {
                    localPosition -= Parent.Position;
                }

                return localPosition;
            }
            set
            {
                Vector2 position = value;

                if (Parent is not null)
                {
                    position += Parent.Position;
                }

                _position = position;
            }
        }

        public Size Size { get; set; }

        public Transform Parent { get; private set; }

        public void SetParent(Transform parent, bool zeroLocalPosition = false)
        {
            Parent = parent;

            if (zeroLocalPosition)
            {
                LocalPosition = Vector2.Zero;
            }
        }
    }
}
