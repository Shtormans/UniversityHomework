namespace Lab_4;

public class DoctorListHandlerEventArgs : EventArgs
{
    public DoctorListHandlerEventArgs(string collectionName, string change, int changedElement)
    {
        CollectionName = collectionName;
        Change = change;
        ChangedElement = changedElement;
    }
    
    public string CollectionName { get; private set; }
    public string Change { get; private set; }
    public int ChangedElement { get; private set; }

    public override string ToString()
    {
        return $"CollectionName: {CollectionName}, Changes: {Change}, ChangedElement: {ChangedElement}";
    }
}