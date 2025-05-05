namespace Lab_2;

internal class Listener
{
    private readonly List<ListEntry> _entries = new();

    public void OnDoctorsChanged(object source, DoctorsChangedEventArgs<string> args)
    {
        ListEntry entry = new(args.CollectionName, args.UpdateType, args.DoctorProperty, args.Key);
        _entries.Add(entry);
    }

    public override string ToString()
    {
        return string.Join("\n", _entries);
    }
}
