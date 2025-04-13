namespace Lab_4;

public class ListEntry
{
    public ListEntry(string collectionName, string change, int index)
    {
        CollectionName = collectionName;
        Change = change;
        Index = index;
    }

    public string CollectionName { get; private set; }
    public string Change { get; private set; }
    public int Index { get; private set; }

    public override string ToString()
    {
        return $"Collection: {CollectionName}, Change: {Change}, Index: {Index}";
    }
}