namespace Lab_4;

internal class DoctorComparer : IComparer<Doctor>
{
    public int Compare(Doctor? x, Doctor? y)
    {
        if (x is null)
        {
            return -1;
        }

        if (y is null)
        {
            return 1;
        }

        return x.ExperienceYears.CompareTo(y.ExperienceYears);
    }
}
