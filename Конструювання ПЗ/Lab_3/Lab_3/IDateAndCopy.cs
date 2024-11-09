namespace Lab_3;

internal interface IDateAndCopy
{
    public DateTime Date { get; set; }

    public object DeepCopy();
}
