import React from 'react';

interface DynamicContentProps {
  type: string;
}

const DynamicContent = ({ type } : DynamicContentProps) => {
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
              <h2 className="text-3xl font-bold">Add Extras</h2>
            </div>
            <div className="flex items-center">
            <button className="bg-green-500 text-white py-2 px-4 rounded">
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

export default DynamicContent;
