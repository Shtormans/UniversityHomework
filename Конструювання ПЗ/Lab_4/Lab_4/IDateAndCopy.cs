namespace Lab_4;


internal interface IDateAndCopy
{
    public DateTime Date { get; set; }

    public object DeepCopy();
}
