namespace Lab_4;

public class Listener
{
    private List<ListEntry> _entries = new();

    public void OnDoctorAdded(object sender, DoctorListHandlerEventArgs args)
    {
           AddEntry(args);
    }
    
    public void OnDoctorReplaced(object sender, DoctorListHandlerEventArgs args)
    {
        AddEntry(args);
    }

    private void AddEntry(DoctorListHandlerEventArgs args)
    {
        ListEntry entry = new(args.CollectionName, args.Change, args.ChangedElement);
        _entries.Add(entry);
    }

    public override string ToString()
    {
        return string.Join('\n', _entries);
    }
}