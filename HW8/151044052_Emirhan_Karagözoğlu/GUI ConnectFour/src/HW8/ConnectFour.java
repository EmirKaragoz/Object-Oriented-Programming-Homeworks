package HW8;

import java.awt.BorderLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

/**
 * Connect 4 Class
 * @author Emir
 * 
 */
public class ConnectFour{
    /**
     * row number
     */
    private int row;
    /**
     * column number
     */
    private int column;
    /**
     * pvp or pvc
     */
    private int gameType;
    /**
     * to determine move order
     */
    private int move;
    /**
     * game frame
     */
    private final JFrame window;
    /**
     * cell board
     */
    private Cell [][] gameCells;    
    
    /**
     * Inner Cell Class
     * 
     */
    private class Cell{
        private char cell;
        
        public Cell(){
            cell = '.';
        }
        
        public char getCell(){
            return cell;
        }
        
        public void setCell(char option){
            cell = option;
        }
    }
    
    /**
     * 
     * @return bir kolondaki oynanılabilir cell sayısı
     * 
     */
    private int usable(int col){    //bir kolonda kaç adet oynanabilir cell var onu sayıyor
        int sum=0;
        for(int i = 0 ; i<row ;++i){
            if(gameCells[i][col].getCell() == '.')
                ++sum;
        }
        return sum;
    }
    
     /**
     * gönderilen koordinatların oynanabilirliğini kontrol ediyor
     * @return true or false
     * 
     */
    private boolean isLegal(int r, int c){  
        boolean status=false;
	
	if(r < row && r >= 0 && c < column && c >= 0){
            if(gameCells[r][c].getCell()=='.'){
                if(r != row-1 && r+1<=row-1 && gameCells[r+1][c].getCell()!='.')
                    status = true;
                else if(r==row-1)
                    status = true;
            }
	}
	return status;
    }
    
     /**
     * @return oynanabilir bir column return ediyor
     * 
     */
    private int findEmptyColumn(){  
	int status=-1;
        int key = 0;
        for (int i = 0; i < column && key == 0; ++i) {
            for (int j = row - 1; j >= 0 && key == 0; --j) {
                if (gameCells[j][i].getCell() == '.') {
                    status = i;
                    key = 1;
                }
            }
        }
        return status;
    }
    /**
     * tüm 3lü atak fonksiyonlarını içeriyor
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack3() { 
        int status;
        if (attack3Vertical() > 0) {
            status = attack3Vertical();
            return status;
        } else if (attack3Horizontal() > 0) {
            status = attack3Horizontal();
            return status;
        } else if (attack3RightCross() > 0) {
            status = attack3RightCross();
            return status;
        } else if (attack3LeftCross() > 0) {
            status = attack3LeftCross();
            return status;
        } else {
            status = -1;
        }

        return status;
    }
    
    /**
     * yatay üçlü atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack3Horizontal(){    //yatay 3lü atak fonksiyonu
        int status = -1;

        for (int i = row - 1; i >= 0; --i) {
            for (int j = 0; j < column - 2; ++j) {
                if (gameCells[i][j].getCell() == 'O' && gameCells[i][j + 1].getCell() == 'O' && gameCells[i][j + 2].getCell() == 'O') {
                    if (isLegal(i, j - 1)) {
                        status = j - 1;
                    } else if (isLegal(i, j + 3)) {
                        status = j + 3;
                    }
                }
            }
        }
        return status;
    }
    /**
     * dikey üçlü atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack3Vertical() { //dikey 3lü atak fonksiyonu
        int status = -1;

        for (int i = 0; i < column; ++i) {
            for (int j = row - 1; j > 2; --j) {
                if (gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i].getCell() == 'O' && gameCells[j - 2][i].getCell() == 'O') {
                    if (isLegal(j - 3, i)) {
                        status = i;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * sağçapraz üçlü atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack3RightCross() {   //sağ çapraz 3lü atak fonksiyonu
        int status = -1;

        for (int j = row - 1; j > 2; --j) {
            for (int i = 0; i < column - 3; ++i) {
                if (gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i + 1].getCell() == 'O' && gameCells[j - 2][i + 2].getCell() == 'O') {
                    if (isLegal(j - 3, i + 3)) {
                        status = i + 3;
                    } else if (isLegal(j + 1, i - 1)) {
                        status = i - 1;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * solçapraz üçlü atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack3LeftCross() {    //solçapraz üçlü atak fonksiyonu
        int status = -1;

        for (int j = row - 1; j > 2; --j) {
            for (int i = column - 1; i > 2; --i) {
                if (gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i - 1].getCell() == 'O' && gameCells[j - 2][i - 2].getCell() == 'O') {
                    if (isLegal(j - 3, i - 3)) {
                        status = i - 3;
                    } else if (isLegal(j + 1, i + 1)) {
                        status = i + 1;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * tüm üçlü defans fonksiyonlarını içeriyor
     * @return column or -1(bulamama durumu)
     * 
     */
    private int defence3() { 
        int status;
        if (defence3Vertical() > 0) {
            status = defence3Vertical();
            return status;
        } else if (defence3Horizontal() > 0) {
            status = defence3Horizontal();
            return status;
        } else if (defence3RightCross() > 0) {
            status = defence3RightCross();
            return status;
        } else if (defence3LeftCross() > 0) {
            status = defence3LeftCross();
            return status;
        } else {
            status = -1;
        }

        return status;
    }
    
    /**
     * yatay üçlü defans fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int defence3Horizontal(){   //yatay 3lü defans fonksiyonu
        int status = -1;

        for (int i = row - 1; i >= 0; --i) {
            for (int j = 0; j < column - 2; ++j) {
                if (gameCells[i][j].getCell() == 'X' && gameCells[i][j + 1].getCell() == 'X' && gameCells[i][j + 2].getCell() == 'X') {
                    if (isLegal(i, j - 1)) {
                        status = j - 1;
                        return status;
                    } else if (isLegal(i, j + 3)) {
                        status = j + 3;
                        return status;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * dikey üçlü defans fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int defence3Vertical() {    //dikey üçlü defans fonksiyonu
        int status = -1;

        for (int i = 0; i < column; ++i) {
            for (int j = row - 1; j > 2; --j) {
                if (gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i].getCell() == 'X' && gameCells[j - 2][i].getCell() == 'X') {
                    if (isLegal(j - 3, i)) {
                        status = i;
                        return status;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * sağçapraz üçlü defans fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int defence3RightCross() {  // sağ çapraz üçlü defans fonksiyonu
        int status = -1;

        for (int j = row - 1; j > 2; --j) {
            for (int i = 0; i < column - 3; ++i) {
                if (gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i + 1].getCell() == 'X' && gameCells[j - 2][i + 2].getCell() == 'X') {
                    if (isLegal(j - 3, i + 3)) {
                        status = i + 3;
                        return status;
                    } else if (isLegal(j + 1, i - 1)) {
                        status = i - 1;
                        return status;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * solçapraz üçlü defans fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int defence3LeftCross() {   //sol çapraz üçlü defans fonksiyonu
        int status = -1;

        for (int j = row - 1; j > 2; --j) {
            for (int i = column - 1; i > 2; --i) {
                if (gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i - 1].getCell() == 'X' && gameCells[j - 2][i - 2].getCell() == 'X') {
                    if (isLegal(j - 3, i - 3)) {
                        status = i - 3;
                        return status;
                    } else if (isLegal(j + 1, i + 1)) {
                        status = i + 1;
                        return status;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * tüm tekli atak fonksiyonlarını içerir
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack1() {
        int status;
        if (attack1Vertical() > 0){
            status = attack1Vertical();
            return status;
        }
        else if (attack1Horizontal() > 0){
            status = attack1Horizontal();
            return status;
        }
        else if (attack1RightCross() > 0){
            status = attack1RightCross();
            return status;
        }
        else if (attack1LeftCross() > 0){
            status = attack1LeftCross();
            return status;
        }
        else 
            status=-1;

        return status;
    }
    
    /**
     * yatay tekli atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack1Horizontal() {   //yatay tekli atak fonksiyonu
        int status = -1;

        for (int i = row - 1; i >= 0; --i) {
            for (int j = 0; j < column; ++j) {
                if (gameCells[i][j].getCell() == 'O') {
                    if (isLegal(i, j - 1)){
                        status = j - 1;
                        return status;
                    }
                    else if(isLegal(i,j+1)){
                        status = j+1;
                        return status;
                    }    
                }
            }
        }
        return status;
    }
    
    /**
     * dikey tekli atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack1Vertical() { //dikey tekli atak fonksiyonu
        int status = -1;

        for (int i = 0; i < column; ++i) {
            for (int j = row - 1; j > 0; --j) {
                if (gameCells[j][i].getCell() == 'O') {
                    if (isLegal(j - 1, i)) {
                        status = i;
                        return status;
                    }
                }
            }
        }
        return status;
    }
    
    /**
     * sağçapraz tekli atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack1RightCross() {  
        int status = -1;

        for (int j = row - 1; j > 0; --j) {
            for (int i = 0; i < column - 1; ++i) {
                if (gameCells[j][i].getCell() == 'O') {
                    if (isLegal(j - 1, i + 1)) {
                        status = i + 1;
                        return status;
                    }

                }
            }
        }
        return status;
    }
    
     /**
     * solçapraz tekli atak fonksiyonu
     * @return column or -1(bulamama durumu)
     * 
     */
    private int attack1LeftCross() {    //solçapraz tekli atak fonksiyonu
        int status = -1;

        for (int j = row - 1; j > 0; --j) {
            for (int i = column - 1; i > 0; --i) {
                if (gameCells[j][i].getCell() == 'O') {
                    if (isLegal(j - 1, i - 1)) {
                        status = i - 1;
                        return status;
                    }
                }
            }
        }
        return status;
    }

    /**
     * Cell boardı initialize eder
     * 
     */
    private void initCell(){    
        gameCells = new Cell[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                gameCells[i][j] = new Cell();
            }
        }
    }
 
    /**
     * Tahtanın dolup dolmadığını kontrol eder
     * @return true or false
     * 
     */
    private boolean fillCheck(){    
        boolean status=true;
	
	for(int i=0 ; i<row ; ++i){
            for(int j=0; j<column ; ++j){
                if(gameCells[i][j].getCell()=='.')
                    return false;
            }
        }
	return status;
    }
    
    /**
     * Checks all
     * @return 0 for togetherness 1 for user1 winner 2 for user2 winner
     * @param jbt jbutton table 2d
     * 
     */
    private int check(JButton [][] jbt) {   //kazananın olup olmadığını kontrol eder
        int status;

        status = horizontalCheck(jbt);
        if (status == 0) {
            status = verticalCheck(jbt);
            if (status == 0) {
                status = rightCrossCheck(jbt);
                if (status == 0) {
                    status = leftCrossCheck(jbt);
                }
            }
        }
        return status;
    }
    
    /**
     * Checks horizontal
     * @return 0 for togetherness 1 for user1 winner 2 for user2 winner
     * @param jbt jbutton table 2d
     * 
     */
    private int horizontalCheck(JButton [][] jbt){//yatay kontrol
        int status = 0;

        for (int i = row - 1; i >= 0; --i) {
            for (int j = 0; j < column - 3; ++j) {
                if ((gameCells[i][j].getCell() == 'X' && gameCells[i][j + 1].getCell() == 'X' && gameCells[i][j + 2].getCell() == 'X' && gameCells[i][j + 3].getCell() == 'X')
                        || (gameCells[i][j].getCell() == 'x' && gameCells[i][j + 1].getCell() == 'x' && gameCells[i][j + 2].getCell() == 'x' && gameCells[i][j + 3].getCell() == 'x')) {
                    //user1 kazandıysa oluşan dörtlüyü işaretle
                    status = 1;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked blue circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[i][j].setIcon(imageIcon);
                    jbt[i][j].setBackground(Color.orange);
                    jbt[i][j+1].setIcon(imageIcon);
                    jbt[i][j+1].setBackground(Color.orange);
                    jbt[i][j+2].setIcon(imageIcon);
                    jbt[i][j+2].setBackground(Color.orange);
                    jbt[i][j+3].setIcon(imageIcon);
                    jbt[i][j+3].setBackground(Color.orange);
                    gameCells[i][j].setCell('x');
                    gameCells[i][j + 1].setCell('x');
                    gameCells[i][j + 2].setCell('x');
                    gameCells[i][j + 3].setCell('x');
                } else if ((gameCells[i][j].getCell() == 'O' && gameCells[i][j + 1].getCell() == 'O' && gameCells[i][j + 2].getCell() == 'O' && gameCells[i][j + 3].getCell() == 'O')
                        || (gameCells[i][j].getCell() == 'o' && gameCells[i][j + 1].getCell() == 'o' && gameCells[i][j + 2].getCell() == 'o' && gameCells[i][j + 3].getCell() == 'o')) {
                    //user2 kazandıysa oluşan dörtlüyü işaratle
                    status = 2;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[i][j].setIcon(imageIcon);
                    jbt[i][j].setBackground(Color.orange);
                    jbt[i][j+1].setIcon(imageIcon);
                    jbt[i][j+1].setBackground(Color.orange);
                    jbt[i][j+2].setIcon(imageIcon);
                    jbt[i][j+2].setBackground(Color.orange);
                    jbt[i][j+3].setIcon(imageIcon);
                    jbt[i][j+3].setBackground(Color.orange);
                    gameCells[i][j].setCell('o');
                    gameCells[i][j + 1].setCell('o');
                    gameCells[i][j + 2].setCell('o');
                    gameCells[i][j + 3].setCell('o');
                }
            }
        }
        return status;
    }
    
    /**
     * Checks vertical
     * @return 0 for togetherness 1 for user1 winner 2 for user2 winner
     * @param jbt jbutton table 2d
     * 
     */
    private int verticalCheck(JButton [][] jbt) {//dikey kontrol
        int status = 0;

        for (int i = 0; i < column; ++i) {
            for (int j = row - 1; j > 2; --j) {
                if ((gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i].getCell() == 'X' && gameCells[j - 2][i].getCell() == 'X' && gameCells[j - 3][i].getCell() == 'X')
                        || (gameCells[j][i].getCell() == 'x' && gameCells[j - 1][i].getCell() == 'x' && gameCells[j - 2][i].getCell() == 'x' && gameCells[j - 3][i].getCell() == 'x')) {
                    //user1 kazandıysa oluşan dörtlüyü işaretle
                    status = 1;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked blue circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i].setIcon(imageIcon);
                    jbt[j-1][i].setBackground(Color.orange);
                    jbt[j-2][i].setIcon(imageIcon);
                    jbt[j-2][i].setBackground(Color.orange);
                    jbt[j-3][i].setIcon(imageIcon);
                    jbt[j-3][i].setBackground(Color.orange);
                    gameCells[j][i].setCell('x');
                    gameCells[j - 1][i].setCell('x');
                    gameCells[j - 2][i].setCell('x');
                    gameCells[j - 3][i].setCell('x');
                } else if ((gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i].getCell() == 'O' && gameCells[j - 2][i].getCell() == 'O' && gameCells[j - 3][i].getCell() == 'O')
                        || (gameCells[j][i].getCell() == 'o' && gameCells[j - 1][i].getCell() == 'o' && gameCells[j - 2][i].getCell() == 'o' && gameCells[j - 3][i].getCell() == 'o')) {
                    //user2 kazandıysa oluşan dörtlüyü işaretle
                    status = 2;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i].setIcon(imageIcon);
                    jbt[j-1][i].setBackground(Color.orange);
                    jbt[j-2][i].setIcon(imageIcon);
                    jbt[j-2][i].setBackground(Color.orange);
                    jbt[j-3][i].setIcon(imageIcon);
                    jbt[j-3][i].setBackground(Color.orange);
                    gameCells[j][i].setCell('o');
                    gameCells[j - 1][i].setCell('o');
                    gameCells[j - 2][i].setCell('o');
                    gameCells[j - 3][i].setCell('o');
                }
            }
        }
        return status;
    }
    
    /**
     * Checks rightcross
     * @return 0 for togetherness 1 for user1 winner 2 for user2 winner
     * @param jbt jbutton table 2d
     * 
     */
    private int rightCrossCheck(JButton [][] jbt) { //sağ çapraz kontrol
        int status = 0;

        for (int j = row - 1; j > 2; --j) {
            for (int i = 0; i < column - 3; ++i) {
                if ((gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i + 1].getCell() == 'X' && gameCells[j - 2][i + 2].getCell() == 'X' && gameCells[j - 3][i + 3].getCell() == 'X')
                        || (gameCells[j][i].getCell() == 'x' && gameCells[j - 1][i + 1].getCell() == 'x' && gameCells[j - 2][i + 2].getCell() == 'x' && gameCells[j - 3][i + 3].getCell() == 'x')) {
                    //user1 kazandıysa oluşan dörtlüyü işaretle
                    status = 1;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked blue circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i+1].setIcon(imageIcon);
                    jbt[j-1][i+1].setBackground(Color.orange);
                    jbt[j-2][i+2].setIcon(imageIcon);
                    jbt[j-2][i+2].setBackground(Color.orange);
                    jbt[j-3][i+3].setIcon(imageIcon);
                    jbt[j-3][i+3].setBackground(Color.orange);
                    gameCells[j][i].setCell('x');
                    gameCells[j - 1][i + 1].setCell('x');
                    gameCells[j - 2][i + 2].setCell('x');
                    gameCells[j - 3][i + 3].setCell('x');
                } else if ((gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i + 1].getCell() == 'O' && gameCells[j - 2][i + 2].getCell() == 'O' && gameCells[j - 3][i + 3].getCell() == 'O')
                        || (gameCells[j][i].getCell() == 'o' && gameCells[j - 1][i + 1].getCell() == 'o' && gameCells[j - 2][i + 2].getCell() == 'o' && gameCells[j - 3][i + 3].getCell() == 'o')) {
                    //user2 kazandıysa oluşan dörtlüyü işaretle
                    status = 2;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i+1].setIcon(imageIcon);
                    jbt[j-1][i+1].setBackground(Color.orange);
                    jbt[j-2][i+2].setIcon(imageIcon);
                    jbt[j-2][i+2].setBackground(Color.orange);
                    jbt[j-3][i+3].setIcon(imageIcon);
                    jbt[j-3][i+3].setBackground(Color.orange);
                    gameCells[j][i].setCell('o');
                    gameCells[j - 1][i + 1].setCell('o');
                    gameCells[j - 2][i + 2].setCell('o');
                    gameCells[j - 3][i + 3].setCell('o');
                }
            }
        }
        return status;
    }
    
    /**
     * Checks leftcross
     * @return 0 for togetherness 1 for user1 winner 2 for user2 winner
     * @param jbt jbutton table 2d
     * 
     */
    private int leftCrossCheck(JButton [][] jbt) {//solçapraz kontrol
        int status = 0;

        for (int j = row - 1; j > 2; --j) {
            for (int i = column - 1; i > 2; --i) {
                if ((gameCells[j][i].getCell() == 'X' && gameCells[j - 1][i - 1].getCell() == 'X' && gameCells[j - 2][i - 2].getCell() == 'X' && gameCells[j - 3][i - 3].getCell() == 'X')
                        || (gameCells[j][i].getCell() == 'x' && gameCells[j - 1][i - 1].getCell() == 'x' && gameCells[j - 2][i - 2].getCell() == 'x' && gameCells[j - 3][i - 3].getCell() == 'x')) {
                    //user1 kazandıysa oluşan dörtlüyü işaretle
                    status = 1;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked blue circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i-1].setIcon(imageIcon);
                    jbt[j-1][i-1].setBackground(Color.orange);
                    jbt[j-2][i-2].setIcon(imageIcon);
                    jbt[j-2][i-2].setBackground(Color.orange);
                    jbt[j-3][i-3].setIcon(imageIcon);
                    jbt[j-3][i-3].setBackground(Color.orange);
                    gameCells[j][i].setCell('x');
                    gameCells[j - 1][i - 1].setCell('x');
                    gameCells[j - 2][i - 2].setCell('x');
                    gameCells[j - 3][i - 3].setCell('x');
                } else if ((gameCells[j][i].getCell() == 'O' && gameCells[j - 1][i - 1].getCell() == 'O' && gameCells[j - 2][i - 2].getCell() == 'O' && gameCells[j - 3][i - 3].getCell() == 'O')
                        || (gameCells[j][i].getCell() == 'o' && gameCells[j - 1][i - 1].getCell() == 'o' && gameCells[j - 2][i - 2].getCell() == 'o' && gameCells[j - 3][i - 3].getCell() == 'o')) {
                    //user2 kazandıysa oluşan dörtlüyü işaretle
                    status = 2;
                    ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\ticked red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                    jbt[j][i].setIcon(imageIcon);
                    jbt[j][i].setBackground(Color.orange);
                    jbt[j-1][i-1].setIcon(imageIcon);
                    jbt[j-1][i-1].setBackground(Color.orange);
                    jbt[j-2][i-2].setIcon(imageIcon);
                    jbt[j-2][i-2].setBackground(Color.orange);
                    jbt[j-3][i-3].setIcon(imageIcon);
                    jbt[j-3][i-3].setBackground(Color.orange);
                    gameCells[j][i].setCell('o');
                    gameCells[j - 1][i - 1].setCell('o');
                    gameCells[j - 2][i - 2].setCell('o');
                    gameCells[j - 3][i - 3].setCell('o');
                }
            }
        }
        return status;
    }
    
    /**
     * Oyunun sonlanıp sonlanmadığını kontrol eder
     * @return end or not
     * @param jbt jbutton table 2d
     * 
     */
    private boolean end(JButton [][] jbt){  
        if(check(jbt)!=0 || fillCheck()==true)
            return true;
	else
            return false;
    }
      
    ConnectFour(){  //constructor
        window = new JFrame("Connect 4");
        window.setDefaultCloseOperation(window.EXIT_ON_CLOSE);
        window.setVisible(true);
        window.setSize(800,600);
        window.setLocation(275,70); 
        move = 0;
    }
    
    /**
     * Game menu , includes gametype buttons event handlers and size text field  
     * @return JFrame of game
     * 
     */
    private JFrame menu(){  
        //game type buttons
        JButton single = new JButton("Player VS Player");
        JButton multiple = new JButton("Player VS Computer");
        
        JPanel buttonPanel = new JPanel();
        buttonPanel.setBackground(Color.YELLOW);
        
        buttonPanel.add(single);
        single.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)  //event handler
            {
                gameType = 1;
                single.setBackground(Color.green);
                multiple.setBackground(Color.red);
                
            }
        });
        
        buttonPanel.add(multiple);
        multiple.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)  //event handler
            {
                gameType = 2;
                single.setBackground(Color.red);
                multiple.setBackground(Color.green);
                
            }
        });
        
        JPanel sizePanel = new JPanel();
        sizePanel.setBackground(Color.BLUE);
        //text field size girilmesi için
        JTextField size = new JTextField("Enter a Size ->",8);
        size.setEditable(false);
        size.setBackground(Color.ORANGE);
        JTextField input = new JTextField(3);
        input.setBackground(Color.ORANGE);
        JButton enter = new JButton("Enter");
        sizePanel.add(size);
        sizePanel.add(input);
        sizePanel.add(enter);
        
        JPanel user1Panel = new JPanel();
        user1Panel.setBackground(Color.BLUE);
        JLabel user1 = new JLabel();
        user1.setIcon(new ImageIcon("src\\user 1.png"));    //user1 symbol image
        user1Panel.add(user1);
        
        JPanel user2Panel = new JPanel();
        user2Panel.setBackground(Color.BLUE);
        JLabel user2 = new JLabel();
        user2.setIcon(new ImageIcon("src\\user 2.png"));    //user2 symbol image
        user2Panel.add(user2);
        
        enter.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)  //event handler
            {
                String temp = input.getText();
                //girilen size ı okur ve integera çevirir
                int finalSize=0;
                for(int j=temp.length()-1,k=0; j>=0 ;--j,++k)
                    finalSize+= Character.getNumericValue(temp.charAt(j))*Math.pow(10, k);
                if(finalSize >= 4){ //min sizedan büyükse...
                    row=column=finalSize;
                    initCell();
                    if(gameType == 1 || gameType == 2){
                        buttonPanel.setVisible(false);
                        sizePanel.setVisible(false);
                        playGame();
                    }
                    else
                        JOptionPane.showMessageDialog(null,"Please choose a Game Type!");
                }
                else
                    JOptionPane.showMessageDialog(null,"Invalid Size. Try againg!");
            }
        });
        //panels placement
        window.add(buttonPanel,BorderLayout.NORTH);
        window.add(sizePanel,BorderLayout.CENTER);
        window.add(user1Panel,BorderLayout.WEST);
        window.add(user2Panel,BorderLayout.EAST);
     
        window.validate();
 
        return window;
    }
    
    /**
     * Plays game and includes button event handlers
     * @return JFrame of game
     * 
     */
    private JFrame playGame(){
        
        JPanel board = new JPanel();
        board.setLayout(new GridLayout(row,column));
        
        //cell button 2d array
        JButton[][] cellButtons = new JButton[row][column];
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column ; ++j) {
                cellButtons[i][j] = new JButton();
            }
        }
        
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column ; ++j) {
                int temp_i = i;
                int temp_j = j;
                
                cellButtons[temp_i][temp_j] = new JButton();
                ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\empty circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                cellButtons[temp_i][temp_j].setIcon(imageIcon);
                cellButtons[temp_i][temp_j].setBackground(Color.orange);
                
                
                
                cellButtons[temp_i][temp_j].addActionListener(new ActionListener() 
                {
                    public void actionPerformed(ActionEvent e) //event handler
                    {
                        int computerEntryKey = 0;
                        if(usable(temp_j) != 0){
                            if(move%2 == 0){    //sıra user1 de ise seçilen columna oyna
                                ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\blue circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                                cellButtons[usable(temp_j)-1][temp_j].setIcon(imageIcon);
                                cellButtons[usable(temp_j)-1][temp_j].setBackground(Color.orange);

                                gameCells[usable(temp_j)-1][temp_j].setCell('X');
                                ++move;
                                if (end(cellButtons)) { //oyun sonlandıysa kazandı mesajını bas ve yeniden başlat
                                    if (check(cellButtons) == 1) {
                                        JOptionPane.showMessageDialog(null, "User 1 Winner");
                                    }
                                    else {
                                        JOptionPane.showMessageDialog(null, "The game ended in a draw!");
                                    }
                                    computerEntryKey = 1;
                                    window.dispose();
                                    String[] arg = new String[10];
                                    arg[0] = "";
                                    main(arg);
                                }
                            }
                            else if(move%2 == 1 && gameType == 1){  //oyun modu pvp ise ve sıra user2 iki de ise seçilen columna oyna
                                ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                                cellButtons[usable(temp_j)-1][temp_j].setIcon(imageIcon);
                                cellButtons[usable(temp_j)-1][temp_j].setBackground(Color.orange);

                                gameCells[usable(temp_j)-1][temp_j].setCell('O');
                                ++move;
                                if (end(cellButtons)) { //oyun sonlandıysa kazandı mesajını bas ve yeniden başlat
                                    if (check(cellButtons) == 2) {
                                        JOptionPane.showMessageDialog(null, "User 2 Winner");
                                    } else {
                                        JOptionPane.showMessageDialog(null, "The game ended in a draw!");
                                    }

                                    window.dispose();
                                    String[] arg = new String[10];
                                    arg[0] = "";
                                    main(arg);
                                }
                            }
                            if(move%2 == 1 && gameType == 2 && computerEntryKey == 0){//pvc modunda computerın sırası ise oynar
                                ImageIcon imageIcon = new ImageIcon(new ImageIcon("src\\red circle.png").getImage().getScaledInstance(500 / row, 500 / column, 1));
                                int tmpcol = attack3();
                                if(tmpcol<0)
                                    tmpcol = defence3();
                                if(tmpcol < 0)
                                    tmpcol = attack1();
                                if(tmpcol < 0)
                                    tmpcol = findEmptyColumn();
                                    
                                int tmprow = usable(tmpcol)- 1;
                                
                                cellButtons[tmprow][tmpcol].setIcon(imageIcon);
                                cellButtons[tmprow][tmpcol].setBackground(Color.orange);

                                gameCells[tmprow][tmpcol].setCell('O');
                                ++move;
                                if (end(cellButtons)) {//oyun sonlandıysa kazandı mesajını bas ve yeniden başlat
                                    if (check(cellButtons) == 2) {
                                        JOptionPane.showMessageDialog(null, "Computer Winner");
                                    } 
                                    else {
                                        JOptionPane.showMessageDialog(null, "The game ended in a draw!");
                                    }

                                    window.dispose();
                                    String[] arg = new String[10];
                                    arg[0] = "";
                                    main(arg);
                                }
                            }
                        }
                    }
                });
            }
        }
        //cell button 2d arrayini gridlayout olan board paneline ekler
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column ; ++j) {
                board.add(cellButtons[i][j]);
            }
        }
        
        window.add(board);
        return window;
    }

    /**
     * Main Class
     * @param args Comment line arguments
     * 
     */
    public static void main(String[]args){
        //obje oluşturup oyunu başlatır
        ConnectFour obje = new ConnectFour();
        obje.menu();
    }
}


   

