namespace Lab_2;

internal interface IDateAndCopy
{
    public DateTime Date { get; set; }

    public object DeepCopy();
}
