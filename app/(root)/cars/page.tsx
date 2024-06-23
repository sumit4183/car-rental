import CarCard from "@/components/CarCard";
import DynamicBar from "@/components/DynamicBar";
import FilterSidebar from "@/components/FilterSidebar";
import ProgressBar from "@/components/ProgressBar";
import Link from "next/link";

const cars = [
  {
    class: 'Standard',
    make: 'Volkswagen',
    model: 'Jetta',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
  {
    class: 'Compact',
    make: 'Hyundai',
    model: 'Verna',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
  {
    class: 'Standard',
    make: 'Volkswagen',
    model: 'Jetta',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
  {
    class: 'Compact',
    make: 'Volkswagen',
    model: 'Jetta',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
  {
    class: 'Standard',
    make: 'Volkswagen',
    model: 'Jetta',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
  {
    class: 'Standard',
    make: 'Volkswagen',
    model: 'Jetta',
    avgDayRate: 123.72,
    estTotal: 859.74,
    imageUrl: '/car.jpg', // Replace with the actual path to the car image
  },
];

const Cars = () => {

  return (
    <div>
      <DynamicBar type="CarListing"/>
      <div className="container mx-auto flex px-4 py-6">
        <FilterSidebar />
        <div className="w-3/4">
          <h1 className="text-4xl font-bold mb-8">Available Cars</h1>
          <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-8">
            {cars.map((car, index) => (
                <CarCard key={index} car={car} />
            ))}
          </div>
        </div>
      </div>
      {/* Use the query parameters to filter and display available cars */}
    </div>
  );
};

export default Cars;
