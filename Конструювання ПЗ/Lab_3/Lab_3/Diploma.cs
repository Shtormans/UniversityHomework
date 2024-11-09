namespace Lab_3;

internal class Diploma
{
    public Diploma() : this("Default Organization", "DefaultQualification", DateTime.UtcNow)
    {

    }

    public Diploma(string organization, string qualification, DateTime issueDate)
    {
        Organization = organization;
        Qualification = qualification;
        IssueDate = issueDate;
    }

    public string Organization { get; set; } = string.Empty;
    public string Qualification { get; set; } = string.Empty;
    public DateTime IssueDate { get; set; }

    public override string ToString()
    {
        return $"{nameof(Organization)}: {Organization},\n{nameof(Qualification)}: {Qualification},\n{nameof(IssueDate)}: {IssueDate:d}";
    }

    public Diploma Clone()
    {
        return (Diploma)MemberwiseClone();
    }
}
