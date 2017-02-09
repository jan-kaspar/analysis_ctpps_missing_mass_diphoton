import root;
import pad_layout;

string rows[];
rows.push("diproton");
rows.push("diphoton");
rows.push("missing");

string cols[];
cols.push("px");
cols.push("py");
cols.push("pz");
cols.push("pT");
cols.push("m");

string f1 = "../../output/test-full/distributions.root";

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int ci : cols.keys)
{
	NewPad(false);
	label("{\SetFontSizesXX " + cols[ci] + "}");
}

for (int ri : rows.keys)
{
	NewRow();

	NewPad(false);
	label("{\SetFontSizesXX " + rows[ri] + "}");

	for (int ci : cols.keys)
	{
		NewPad(cols[ci] + "$\ung{GeV}$");

		draw(RootGetObject(f1, "without cuts/h_" + rows[ri] + "_" + cols[ci]), "vl", blue);
	}
}
