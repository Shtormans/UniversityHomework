using System.Runtime.Intrinsics.Arm;

namespace Lab_2;

public class Doctor
{
    private Person _person;
    private string _specialty;
    private Category _category;
    private int _experienceYears;
    private Diploma[] _diplomas;

    public Doctor() : this(new(), "Default Specialty", default, 1)
    {
        
    }

    public Doctor(Person person, string specialty, Category category, int experienceYears)
    {
        _person = person;
        _specialty = specialty;
        _category = category;
        _experienceYears = experienceYears;

        _diplomas = [];
    }

    public Person Person
    {
        get => _person;
        set => _person = value;
    }

    public string Specialty
    {
        get => _specialty;
        set => _specialty = value;
    }

    public Category Category
    {
        get => _category;
        set => _category = value;
    }

    public int ExperienceYears
    {
        get => _experienceYears; 
        set => _experienceYears = value;
    }

    public Diploma[] Diplomas
    {
        get => _diplomas; 
        set => _diplomas = value;
    }

    public Diploma Diploma => _diplomas.MinBy(diploma => diploma.IssueDate)!;

    public void AddDiplomas(params Diploma[] diplomas)
    {
        _diplomas = _diplomas.Concat(diplomas).ToArray();
    }

    public override string ToString()
    {
        return $"{
            nameof(Person)}: {Person},\n{
            nameof(Specialty)}: {Specialty},\n{
            nameof(Category)}: {Category},\n{
            nameof(ExperienceYears)}: {ExperienceYears},\n{
            nameof(Diplomas)}:\n{string.Join<Diploma>(";\n", Diplomas)}";
    }

    public string ToShortString()
    {
        return $"{
            nameof(Person)}: {Person},\n{
            nameof(Specialty)}: {Specialty},\n{
            nameof(Category)}: {Category},\n{
            nameof(ExperienceYears)}: {ExperienceYears}";
    }
}
