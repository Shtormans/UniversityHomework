namespace Lab_2;

internal class Patient : Person
{
    public Patient() : this(new(), "Default", DateTime.UtcNow)
    {
        
    }

    public Patient(Person person, string diagnosis, DateTime admissionDate)
    {
        Name = person.Name;
        Surname = person.Surname;
        Birthday = person.Birthday;

        Diagnosis = diagnosis;
        AdmissionDate = admissionDate;
    }

    public string Diagnosis { get; set; } = string.Empty;
    public DateTime AdmissionDate { get; set; }

    public override string ToString()
    {
        return $"{base.ToString()},\nDiagnosis: {Diagnosis},\nAdmissionDate: {AdmissionDate:d}";
    }

    public Patient Clone()
    {
        return (Patient)MemberwiseClone();
    }
}
