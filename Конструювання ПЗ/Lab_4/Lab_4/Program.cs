using Lab_4;
using System.Collections.Specialized;
using System.Diagnostics;

internal class Program
{
    private static void Main(string[] args)
    {
        DoctorCollection doctorCollection = new DoctorCollection();
        doctorCollection.AddDefaults();

        Console.WriteLine("Simple");
        Console.WriteLine();
        Console.WriteLine(doctorCollection.ToShortString());
        Console.WriteLine();

        doctorCollection.SortBySurname();

        Console.WriteLine("Sort by username");
        Console.WriteLine();
        Console.WriteLine(doctorCollection.ToShortString());
        Console.WriteLine();

        doctorCollection.SortByBirthday();

        Console.WriteLine("Sort by birthday");
        Console.WriteLine();
        Console.WriteLine(doctorCollection.ToShortString());
        Console.WriteLine();

        doctorCollection.SortByExperience();

        Console.WriteLine("Sort by experience");
        Console.WriteLine();
        Console.WriteLine(doctorCollection.ToShortString());
        Console.WriteLine();

        int collectionSize = InputCount();
        TestCollections testCollections = new(collectionSize);

        Console.WriteLine("\n\n");
        Console.WriteLine("First");

        Doctor firstDoctor = TestCollections.CreateSimpleInstance(0);

        Console.WriteLine($"{nameof(testCollections.CalculateGenericListTimestamp)}, {testCollections.CalculateGenericListTimestamp(firstDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringListTimestamp)}, {testCollections.CalculateStringListTimestamp(firstDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryKeyTimestamp)}, {testCollections.CalculateGenericDictionaryKeyTimestamp(firstDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryKeyTimestamp)}, {testCollections.CalculateStringDictionaryKeyTimestamp(firstDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryValueTimestamp)}, {testCollections.CalculateGenericDictionaryValueTimestamp(firstDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryValueTimestamp)}, {testCollections.CalculateStringDictionaryValueTimestamp(firstDoctor).TotalMilliseconds}");

        Console.WriteLine("\n\n");
        Console.WriteLine("Middle");

        Doctor middleDoctor = TestCollections.CreateSimpleInstance((collectionSize - 1) / 2);

        Console.WriteLine($"{nameof(testCollections.CalculateGenericListTimestamp)}, {testCollections.CalculateGenericListTimestamp(middleDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringListTimestamp)}, {testCollections.CalculateStringListTimestamp(middleDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryKeyTimestamp)}, {testCollections.CalculateGenericDictionaryKeyTimestamp(middleDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryKeyTimestamp)}, {testCollections.CalculateStringDictionaryKeyTimestamp(middleDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryValueTimestamp)}, {testCollections.CalculateGenericDictionaryValueTimestamp(middleDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryValueTimestamp)}, {testCollections.CalculateStringDictionaryValueTimestamp(middleDoctor).TotalMilliseconds}");

        Console.WriteLine("\n\n");
        Console.WriteLine("Last");

        Doctor lastDoctor = TestCollections.CreateSimpleInstance(collectionSize - 1);

        Console.WriteLine($"{nameof(testCollections.CalculateGenericListTimestamp)}, {testCollections.CalculateGenericListTimestamp(lastDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringListTimestamp)}, {testCollections.CalculateStringListTimestamp(lastDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryKeyTimestamp)}, {testCollections.CalculateGenericDictionaryKeyTimestamp(lastDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryKeyTimestamp)}, {testCollections.CalculateStringDictionaryKeyTimestamp(lastDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryValueTimestamp)}, {testCollections.CalculateGenericDictionaryValueTimestamp(lastDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryValueTimestamp)}, {testCollections.CalculateStringDictionaryValueTimestamp(lastDoctor).TotalMilliseconds}");

        Console.WriteLine("\n\n");
        Console.WriteLine("Doesn't exist");

        Doctor notExistDoctor = TestCollections.CreateSimpleInstance(-1);

        Console.WriteLine($"{nameof(testCollections.CalculateGenericListTimestamp)}, {testCollections.CalculateGenericListTimestamp(notExistDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringListTimestamp)}, {testCollections.CalculateStringListTimestamp(notExistDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryKeyTimestamp)}, {testCollections.CalculateGenericDictionaryKeyTimestamp(notExistDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryKeyTimestamp)}, {testCollections.CalculateStringDictionaryKeyTimestamp(notExistDoctor.Surname).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateGenericDictionaryValueTimestamp)}, {testCollections.CalculateGenericDictionaryValueTimestamp(notExistDoctor).TotalMilliseconds}");
        Console.WriteLine($"{nameof(testCollections.CalculateStringDictionaryValueTimestamp)}, {testCollections.CalculateStringDictionaryValueTimestamp(notExistDoctor).TotalMilliseconds}");
    }

    private static int InputCount()
    {
        while (true)
        {
            Console.WriteLine("Input count");

            if (int.TryParse(Console.ReadLine(), out int count) && count > 0)
            {
                return count;
            }
        }
    }
}