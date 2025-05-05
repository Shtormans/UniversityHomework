using System.Runtime.CompilerServices;
using System.Text;

namespace Lab_2;

internal class DoctorsChangedEventArgs<TKey> : EventArgs
{

    public DoctorsChangedEventArgs(string collectionName, DoctorUpdateType updateType, string doctorProperty, TKey key)
    {
        CollectionName = collectionName;
        UpdateType = updateType;
        DoctorProperty = doctorProperty;
        Key = key;
    }

    public string CollectionName { get; set; }
    public DoctorUpdateType UpdateType { get; set; }
    public string DoctorProperty { get; set; }
    public TKey Key { get; set; }

    public override string ToString()
    {
        StringBuilder builder = new();

        builder.Append("CollectionName = ");
        builder.Append(CollectionName);
        builder.Append(", UpdateType = ");
        builder.Append(UpdateType);
        builder.Append(", DoctorProperty = ");
        builder.Append(DoctorProperty);
        builder.Append(", Key = ");
        builder.Append(Key);

        return builder.ToString();
    }
}
