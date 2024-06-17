import Link from 'next/link';

const FeaturedCars = () => {
  const cars = [
    { id: 1, make: 'Toyota', model: 'Camry', rate: 50, image: '/car1.jpg' },
    { id: 2, make: 'Honda', model: 'Civic', rate: 45, image: '/car2.jpg' },
    { id: 3, make: 'Ford', model: 'Mustang', rate: 70, image: '/car3.jpg' },
  ];

  return (
    <div className="container mx-auto my-16">
      <h2 className="text-4xl font-bold text-center mb-8">Featured Cars</h2>
      <div className="grid grid-cols-3 gap-4">
        {cars.map(car => (
          <div key={car.id} className="border p-4 rounded-lg">
            {/* <Image src={car.image} alt={`${car.make} ${car.model}`} className="w-full h-48 object-cover mb-4" /> */}
            <h3 className="text-2xl font-bold">{car.make} {car.model}</h3>
            <p>${car.rate} per day</p>
            <Link href={`/cars/${car.id}`} className="text-blue-500 mt-2 inline-block">
              View Details
            </Link>
          </div>
        ))}
      </div>
    </div>
  );
};

export default FeaturedCars;
