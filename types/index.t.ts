declare interface ProgressTrackerProps {
    rentalDetails: string;
    pickupReturn: string;
    vehicle: string;
    extras: string;
}

declare interface CarCardProps {
    car: {
        class: string;
        make: string;
        model: string;
        avgDayRate: number;
        estTotal: number;
        imageUrl: string;
    };
}