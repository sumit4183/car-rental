"use client";

import { usePathname, useRouter } from 'next/navigation';
import { useEffect, useState } from 'react';
import Cookies from 'js-cookie';

const ProgressBar = () => {
  const currentPath = usePathname();
  const router = useRouter();

  const [rentalData, setRentalData] = useState({
    pickupLocation: '',
    dropoffLocation: '',
    pickupDate: '',
    pickupTime: '',
    dropoffDate: '',
    dropoffTime: '',
    selectedCar: '',
    extras: '',
  });

  const fetchRentalData = () => {
    const storedData = localStorage.getItem('rentalData');
    if (storedData) {
      setRentalData(JSON.parse(storedData));
    }
  };

  useEffect(() => {
    fetchRentalData();
  }, [currentPath]);

  useEffect(() => {
    const handleRouteChange = () => {
      fetchRentalData();
    };

    window.addEventListener('popstate', handleRouteChange);

    return () => {
      window.removeEventListener('popstate', handleRouteChange);
    };
  }, []);
  

  return (
    <div className="bg-gray-100 py-4">
      <div className="container mx-auto flex items-center justify-center px-4">
        <div className="flex items-center">
          <div>
            <span className="font-bold">RENTAL DETAILS</span>
            <div>{rentalData.pickupDate}, {rentalData.pickupTime}</div>
            <div>{rentalData.dropoffDate}, {rentalData.dropoffTime}</div>
          </div>
          <div className="mx-8 text-4xl">→</div>
        </div>

        <div className="flex items-center">
          <div>
            <span className="font-bold">PICK-UP & RETURN</span>
            <div>Pick-up Location: {rentalData.pickupLocation}</div>
            <div>Drop-off Location: {rentalData.dropoffLocation}</div>
          </div>
          <div className="mx-8 text-4xl">→</div>
        </div>

        <div className="flex items-center">
          <div className="text-black">
            <span className="font-bold">VEHICLE</span>
            {currentPath === "/cars" ? (
              <div>Select</div>
            ) : (
              rentalData.selectedCar ? (
                <div>{rentalData.selectedCar}</div>
              ) : null
            )}
          </div>
          <div className="mx-8 text-4xl">→</div>
        </div>

        <div className="flex items-center">
          <div className="text-black">
            <span className="font-bold">EXTRAS</span>
            {currentPath === "/cars/options" ? (
              <div>Select</div>
            ) : (
              rentalData.extras ? (
                <div>{rentalData.extras}</div>
              ) : null
            )}
          </div>
          <div className="mx-8 text-4xl">→</div>
        </div>

        <div className="flex items-center">
          <div className="text-black">
            <span className="font-bold">REVIEW & RESERVE</span>
          </div>
        </div>
      </div>
    </div>
  );
}

export default ProgressBar;
