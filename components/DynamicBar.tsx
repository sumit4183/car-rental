"use client"

import { usePathname, useRouter } from 'next/navigation';
import React, { useEffect, useState } from 'react';

interface DynamicBarProps {
  type: string;
}

const DynamicBar = ({ type } : DynamicBarProps) => {
  const currentPath = usePathname();
  
  const [activeTab, setActiveTab] = useState('');
  const router = useRouter();

  const handleButtonClick = (tab: string, route: string) => {
    setActiveTab(tab);
    router.push(route);
  };

  useEffect(() => {
    if (currentPath === '/cars/options/protection') {
      setActiveTab('Protection');
    } else if (currentPath === '/cars/options/equipment') {
      setActiveTab('Equipment');
    }
  }, [currentPath]);

  const renderButtons = () => (
    <div className="flex space-x-4">
      <button
        onClick={() => handleButtonClick('Protection', '/cars/options/protection')}
        className={`flex items-center py-2 px-4 rounded ${activeTab === 'Protection' ? 'border-b-2 border-blue-500 text-blue-500' : 'text-gray-500'}`}
      >
        <span className="mr-2">🚨</span>
        Protection & Coverages
      </button>
      <button
        onClick={() => handleButtonClick('Equipment', '/cars/options/equipment')}
        className={`flex items-center py-2 px-4 rounded ${activeTab === 'Equipment' ? 'border-b-2 border-blue-500 text-blue-500' : 'text-gray-500'}`}
      >
        <span className="mr-2">📡</span>
        Equipment & Services
      </button>
    </div>
  );
  
  switch (type) {
    case 'CarListing':
      return (
        <div className="bg-white py-4 border-t-2 border-b-2">
          <div className="container mx-auto flex items-center justify-between px-4">
            <div className="flex items-end">
              <h2 className="text-3xl font-bold">Choose a Vehicle Class</h2>
              <span className="ml-2 text-gray-500">X Results</span>
            </div>
            <div className="flex items-center">
              <span className="mr-2 text-gray-500">SORT BY</span>
              <select className="border p-2 rounded">
                <option value="featured">Featured</option>
                <option value="priceLowHigh">Price: Low to High</option>
                <option value="priceHighLow">Price: High to Low</option>
              </select>
            </div>
          </div>
        </div>
      );
    case 'Options':
      return (
        <div className="bg-white py-4 border-t-2 border-b-2">
          <div className="container mx-auto flex items-center justify-between px-4">
            <div className="flex items-end">
              {renderButtons()}
            </div>
            <div className="flex items-center">
              <button className="bg-blue-500 text-white py-2 px-4 rounded">
                Continue to Review
              </button>
            </div>
          </div>
        </div>
      );
    default:
      return null;
  }
};

export default DynamicBar;
