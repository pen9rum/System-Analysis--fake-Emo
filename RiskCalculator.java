import java.util.List;

public class RiskCalculator {
	
	//輸入類別(String)以輸出該類別的RiskPercent
    public static double calculateCategoryRisk(String category, List<String> barcodes, List<String> invalidBarcodes) {
        int sampleNumber = 0;
        int invalidCount = 0;
        String categoryCode = getCategoryCodeFromName(category);

        //計算該類別的編碼總數
        for (String barcode : barcodes) {
            if (getCategoryCode(barcode).equals(categoryCode)) {
                sampleNumber++;
            }
        }

        //計算該類別的錯誤編碼數
        for (String barcode : invalidBarcodes) {
            if (getCategoryCode(barcode).equals(categoryCode)) {
                invalidCount++;
            }
        }

        return calculateRiskPercent(invalidCount, sampleNumber);
    }

    //取得類別代碼
    private static String getCategoryCode(String barcode) {
        return barcode.length() >= 7 ? barcode.substring(5, 7) : "";
    }

    //根據輸入字串判定類別代碼
    private static String getCategoryCodeFromName(String categoryName) {
        switch (categoryName.toLowerCase()) {
            case "Top":
                return "01";
            case "Pants":
                return "02";
            case "Coat":
                return "03";
            case "Shoes":
                return "04";
            case "Accessories":
                return "05";
            default:
                return "";
        }
    }

    //計算RiskPercent
    private static double calculateRiskPercent(int invalidCount, int totalCount) {
        if (totalCount > 0) {
            return (double) invalidCount / totalCount;
        } else {
            return 0.0;
        }
    }
}
