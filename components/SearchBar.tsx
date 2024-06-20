"use client"

import Link from 'next/link';
import { useRouter } from 'next/navigation';
import React, { useEffect, useState } from 'react'

interface Errors {
  pickupLocation?: string;
  dropoffLocation?: string;
  pickupDate?: string;
  pickupTime?: string;
  dropoffDate?: string;
  dropoffTime?: string;
}

const SearchBar = () => {
  const [sameDropOff, setSameDropOff] = useState(true);
  const [pickupLocation, setPickupLocation] = useState('');
  const [dropoffLocation, setDropoffLocation] = useState('');
  const [pickupDate, setPickupDate] = useState('');
  const [pickupTime, setPickupTime] = useState('');
  const [dropoffDate, setDropoffDate] = useState('');
  const [dropoffTime, setDropoffTime] = useState('');
  const [errors, setErrors] = useState<Errors>({});
  const router = useRouter();

  useEffect(() => {
    const storedData = localStorage.getItem('rentalData');
    if (storedData) {
      const data = JSON.parse(storedData);
      setPickupLocation(data.pickupLocation);
      setDropoffLocation(data.dropoffLocation);
      setPickupDate(data.pickupDate);
      setPickupTime(data.pickupTime);
      setDropoffDate(data.dropoffDate);
      setDropoffTime(data.dropoffTime);
    }
  }, []);

  const handleDropOffChange = (event: React.ChangeEvent<HTMLSelectElement>) => {
    setSameDropOff(event.target.value === 'same');
    setErrors({});
  };

  const handleViewCars = () => {
    const newErrors: Errors = {};
    if (!pickupLocation) newErrors.pickupLocation = 'Pick-up location is required';
    if (!pickupDate) newErrors.pickupDate = 'Pick-up date is required';
    if (!pickupTime) newErrors.pickupTime = 'Pick-up time is required';
    if (!dropoffDate) newErrors.dropoffDate = 'Drop-off date is required';
    if (!dropoffTime) newErrors.dropoffTime = 'Drop-off time is required';
    if (!sameDropOff && !dropoffLocation) newErrors.dropoffLocation = 'Drop-off location is required';

    if (Object.keys(newErrors).length > 0) {
      setErrors(newErrors);
    } else {
      setErrors({});
      const rentalData = {
        pickupLocation,
        dropoffLocation: sameDropOff ? pickupLocation : dropoffLocation,
        pickupDate,
        pickupTime,
        dropoffDate,
        dropoffTime,
      };
      localStorage.setItem('rentalData', JSON.stringify(rentalData));
      router.push('/cars');
    }

    
  };

  return (
    <div  className="bg-white p-6 shadow-md rounded-md w-8/12 mx-auto">
      <div className="flex space-x-4 p-2 items-center justify-between">
        <div className="">
          <select
            onChange={handleDropOffChange}
            className="border p-2 rounded"
          >
            <option value="same">Same Drop-off Location</option>
            <option value="different">Different Drop-off Location</option>
          </select>
        </div>
        <div className="">
          <Link href=""> View / Edit / Cancel</Link>
        </div>
      </div>
      
        
      {sameDropOff ? (
        <div className="flex flex-col items-start md:col-span-2 col-span-6 p-2">
          <label className="text-gray-500" htmlFor="pickupLocation">Pick-up Location</label>
          <input
            type="text"
            id="pickupLocation"
            className="search-input"
            placeholder="Enter location"
            value={pickupLocation}
            onChange={(e) => setPickupLocation(e.target.value)}
          />
          {errors.pickupLocation && <span className="text-red-500">{errors.pickupLocation}</span>}
        </div>
      ) : (
        <div className="grid grid-cols-2 gap-4 p-2">
          <div className="flex flex-col items-start md:col-span-1 col-span-1">
            <label className="text-gray-500" htmlFor="pickupLocation">Pick-up </label>
            <input
              type="text"
              id="pickupLocation"
              className="search-input"
              placeholder="Enter location"
              value={pickupLocation}
              onChange={(e) => setPickupLocation(e.target.value)}
            />
            {errors.pickupLocation && <span className="text-red-500">{errors.pickupLocation}</span>}
          </div>
          <div className="flex flex-col items-start md:col-span-1 col-span-1">
            <label className="text-gray-500" htmlFor="dropoffLocation">Drop-off </label>
            <input
              type="text"
              id="dropoffLocation"
              className="search-input"
              placeholder="Enter location"
              value={dropoffLocation}
              onChange={(e) => setDropoffLocation(e.target.value)}
            />
            {errors.dropoffLocation && <span className="text-red-500">{errors.dropoffLocation}</span>}
          </div>
        </div>
      )}
      <div className="grid grid-cols-1 md:grid-cols-6 gap-4 p-2">
        <div className="search-field">
          <label className="text-gray-500" htmlFor="pickupDate">Pick-up Date</label>
            <input
            type="date"
            id="pickupDate"
            className="search-input"
            value={pickupDate}
            onChange={(e) => setPickupDate(e.target.value)}
          />
          {errors.pickupDate && <span className="text-red-500">{errors.pickupDate}</span>}
        </div>
        <div className="search-field">
          <label className="text-gray-500" htmlFor="pickupTime">Pick-up Time</label>
          <input
            type="time"
            id="pickupTime"
            className="search-input"
            value={pickupTime}
            onChange={(e) => setPickupTime(e.target.value)}
          />
          {errors.pickupTime && <span className="text-red-500">{errors.pickupTime}</span>}
        </div>
        <div className="search-field">
          <label className="text-gray-500" htmlFor="dropoffDate">Drop-off Date</label>
          <input
            type="date"
            id="dropoffDate"
            className="search-input"
            value={dropoffDate}
            onChange={(e) => setDropoffDate(e.target.value)}
          />
          {errors.dropoffDate && <span className="text-red-500">{errors.dropoffDate}</span>}
        </div>
        <div className="search-field">
          <label className="text-gray-500" htmlFor="dropoffTime">Drop-off Time</label>
          <input
            type="time"
            id="dropoffTime"
            className="search-input"
            value={dropoffTime}
            onChange={(e) => setDropoffTime(e.target.value)}
          />
          {errors.dropoffTime && <span className="text-red-500">{errors.dropoffTime}</span>}
        </div>
      </div>
      <div className="">
        <button className="bg-yellow-500 text-white p-2 rounded m-4" onClick={handleViewCars}>
          View Cars
        </button>
      </div>
    </div>
  );
}

export default SearchBar