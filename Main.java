import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of samples: ");
        int numberOfSamples = scanner.nextInt();

        List<String> barcodes = new ArrayList<>();
        System.out.println("Enter the barcodes (enter 'done' to finish):");
        
        while (true) {
            String tempBarcode = scanner.next();
            if ("done".equalsIgnoreCase(tempBarcode)) break;
            barcodes.add(tempBarcode);
        }

        BarcodeSampler sampler = new BarcodeSampler();
        BarcodeProcessor processor = new BarcodeProcessor(sampler);

        List<String> invalidBarcodes = processor.sampleAndCheckBarcodes(numberOfSamples, barcodes);

        System.out.println("\nList of invalid barcodes:");
        for (String barcode : invalidBarcodes) {
            System.out.println("Invalid Barcode: " + barcode);
        }

//風險計算
        System.out.println("\nRisk Percent: ");
        System.out.println("Top: " + RiskCalculator.calculateCategoryRisk("Top",barcodes, invalidBarcodes));
        System.out.println("Pants: " + RiskCalculator.calculateCategoryRisk("Pants", barcodes, invalidBarcodes));
        System.out.println("Coat: " + RiskCalculator.calculateCategoryRisk("Coat", barcodes, invalidBarcodes));
        System.out.println("Shoes: " + RiskCalculator.calculateCategoryRisk("Shoes", barcodes, invalidBarcodes));
        System.out.println("Accessories: " + RiskCalculator.calculateCategoryRisk("Accessories", barcodes, invalidBarcodes));
    }
}