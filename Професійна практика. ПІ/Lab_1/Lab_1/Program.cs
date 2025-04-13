using Lab_4;

internal class Program
{
    private static void Main(string[] args)
    {
        DoctorCollection collection1 = new("Collection 1");
        DoctorCollection collection2 = new("Collection 2");
        
        collection1.AddDefaults();
        collection2.AddDefaults();

        Listener listener1 = new();
        Listener listener2 = new();

        collection1.DoctorAdded += listener1.OnDoctorAdded;
        collection1.DoctorReplaced += listener1.OnDoctorReplaced;
        
        collection2.DoctorAdded += listener2.OnDoctorAdded;
        collection2.DoctorReplaced += listener2.OnDoctorReplaced;



        {
            collection1.AddDoctors(new Doctor());
            collection1.Replace(0, new Doctor());
            
            collection2.AddDoctors(new Doctor());
        }
        
        
        Console.WriteLine("Listener 1:");
        Console.WriteLine(listener1.ToString());
        
        Console.WriteLine("Listener 2:");
        Console.WriteLine(listener2.ToString());
    }
}