import root;
import pad_layout;

string histograms[];
string hist_x_labels[], hist_y_labels[];

histograms.push("h2_diph_pT_vs_diph_m"); hist_x_labels.push("diphoton $m\ung{GeV}$"); hist_y_labels.push("diphoton $p_{\rm T}\ung{GeV}$");
histograms.push("h2_miss_m_vs_diph_m"); hist_x_labels.push("diphoton $m\ung{GeV}$"); hist_y_labels.push("missing $m\ung{GeV}$");
histograms.push("h2_miss_m_vs_dipr_m"); hist_x_labels.push("diproton $m\ung{GeV}$"); hist_y_labels.push("missing $m\ung{GeV}$");
histograms.push("h2_miss_m_vs_diph_pT"); hist_x_labels.push("diphoton $p_{\rm T}\ung{GeV}$"); hist_y_labels.push("missing $m\ung{GeV}$");

string f1 = "../../output/test-full/distributions.root";

//----------------------------------------------------------------------------------------------------

for (int hi : histograms.keys)
{
	NewPad(hist_x_labels[hi], hist_y_labels[hi]);
	scale(Linear, Linear, Log);

	draw(RootGetObject(f1, "without cuts/" + histograms[hi]));
}
