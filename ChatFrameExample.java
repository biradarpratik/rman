import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ChatFrameExample {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Chat Frame");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);

        // Create panel for components
        JPanel panel = new JPanel(new BorderLayout());

        // Create menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu fileMenu = new JMenu("File");
        JMenuItem openItem = new JMenuItem("Open");
        JMenuItem saveAsItem = new JMenuItem("Save As");
        fileMenu.add(openItem);
        fileMenu.add(saveAsItem);
        menuBar.add(fileMenu);
        JMenu helpMenu = new JMenu("Help");
        menuBar.add(helpMenu);
        frame.setJMenuBar(menuBar);

        // Create label
        JLabel enterTextLabel = new JLabel("ENTER TEXT:");

        // Create text field
        JTextField textField = new JTextField(20);

        // Create send button
        JButton sendButton = new JButton("SEND");

        // Create reset button
        JButton resetButton = new JButton("RESET");

        // Create panel for label, text field, send button, and reset button
        JPanel inputPanel = new JPanel(new FlowLayout());
        inputPanel.add(enterTextLabel);
        inputPanel.add(textField);
        inputPanel.add(sendButton);
        inputPanel.add(resetButton);

        // Add input panel to the main panel
        panel.add(inputPanel, BorderLayout.SOUTH);

        // Add action listener for send button
        sendButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String text = textField.getText();
                System.out.println("Sending text: " + text);
                textField.setText("");
            }
        });

        // Add action listener for reset button
        resetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                textField.setText("");
            }
        });

        // Add panel to frame
        frame.getContentPane().add(panel);

        // Display the frame
        frame.setVisible(true);
    }
}
