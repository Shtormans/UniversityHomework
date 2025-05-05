namespace Lab_2
{
    internal delegate TKey KeySelector<TKey>(Doctor doc);
    internal delegate void DoctorsChangedHandler<TKey>(object source, DoctorsChangedEventArgs<TKey> args);

    internal static class Utils
    {
        public static List<Doctor> CreateDoctorList<TKey>(this Dictionary<TKey, Doctor> doctors, string specialty)
        {
            return doctors.Values.Where(doctor => doctor.Specialty == specialty).ToList();
        }
    }
}
