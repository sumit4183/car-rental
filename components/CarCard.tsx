"use client"

import React from 'react';
import Image from 'next/image';
import { useRouter } from 'next/navigation';
import Cookies from 'js-cookie';

const CarCard = ({ car }: CarCardProps) => {
  const router = useRouter();

  const handleClick = () => {
    const storedData = localStorage.getItem('rentalData');
    const rentalData = storedData ? JSON.parse(storedData) : {};
    rentalData.selectedCar = car.class;
    localStorage.setItem('rentalData', JSON.stringify(rentalData));
    router.push('/cars/options');
  };
  
  return (
    <div className="border rounded-lg p-4 shadow-lg bg-white" onClick={handleClick}>
      <Image 
        src={car.imageUrl} 
        alt={`${car.make} ${car.model}`} 
        height={400}
        width={400}
        className="rounded" 
      />
      <div className="mt-4">
        <h2 className="text-xl font-bold">{car.class}</h2>
        <p className="text-gray-600">{`${car.make} ${car.model} or similar`}</p>
        <div className="flex justify-between items-center mt-4">
          <div className="flex space-x-2">
            <span className="flex items-center space-x-1">
              <span>👥</span>
              <span>5</span>
            </span>
            <span className="flex items-center space-x-1">
              <span>🛄</span>
              <span>2</span>
            </span>
            <span className="flex items-center space-x-1">
              <span>📦</span>
              <span>4</span>
            </span>
            <span className="flex items-center space-x-1">
              <span>🚗</span>
              <span>Auto</span>
            </span>
          </div>
        </div>
        <div className="mt-4">
          <p className="text-lg font-semibold">${car.avgDayRate.toFixed(2)} <span className="text-sm">avg/day</span></p>
          <p className="text-gray-600">${car.estTotal.toFixed(2)} est. total</p>
        </div>
      </div>
    </div>
  );
};

export default CarCard;
